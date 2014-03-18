/************************************************************************/
/* Template class for doubly linked list
* Linked list that provides forward and backwards traversals through nodes
@author Eric Stevenson (used provided header file) */
/************************************************************************/
#include <iostream>
/*
* Default constructor
*/
template <class Item, class Order>
DLinkedOrderedList<Item, Order> :: DLinkedOrderedList(): m_head(NULL), m_tail(NULL), m_size(0) {}

/*
* Copy constructor
*/
template <class Item, class Order>
DLinkedOrderedList<Item, Order> :: DLinkedOrderedList(DLinkedOrderedList<Item, Order> const& copy) 
{
	/* empty list */
	if (copy.m_size == 0)
	{
		m_head = NULL;
		m_tail = NULL;
		m_size = 0;
	}
	/* list of size 1 */
	else if (copy.m_size == 1)
	{
		m_size = 1;
		m_head = m_tail = new Node(copy.m_head->value, NULL, NULL);
	}
	/* copy all values from copy list into new list but use new nodes so that the lists are not linked */
	else 
	{
	m_size = copy.m_size;
	m_head = new Node(copy.m_head->value, NULL, NULL); /* For head and tail, we copy the values but not the pointers as we want a "deep" copy */
	m_tail = new Node(copy.m_tail->value, NULL, NULL);
	Node* tmp = m_head; /* temporary node for traversing the new list */
	Node* ctmp = copy.m_head; /* temporary node for traversing the parameter list */
	while(ctmp != copy.m_tail)
	{
		if (ctmp->next != copy.m_tail) /* this will work for all cases except for the node before the tail */
		{
			/* create the next node. Set prev pointer of the new node to the current node, and get the value of the new node from the copy list */
			tmp->next = new Node(ctmp->next->value, NULL, tmp);
			tmp = tmp->next;
			ctmp = ctmp->next;
		}
		else /* tail is already created so we just need to link it to the last node we created */
		{
			/* For the second last node, set the next pointer to the tail, the prev pointer of tail to the second last node, a
			* increment the copy traversal node to break the while loop */
			tmp->next = m_tail;
			m_tail->prev = tmp;
			ctmp = ctmp->next;
		}
	}
	}
}

/*
* Destructor
*/
template <class Item, class Order>
DLinkedOrderedList<Item, Order> :: ~DLinkedOrderedList() 
{
	Node *current = m_head, *nextNode;
	while (current != NULL)
	{
		nextNode = current->next;
		delete current;
		current = nextNode;
	}	
}

/*
* @return the number of nodes in the list
*/
template <class Item, class Order>
unsigned int DLinkedOrderedList<Item, Order> :: size() const 
{
	return m_size;
}

/*
* @return true if the list is empty
*/
template <class Item, class Order>
bool DLinkedOrderedList<Item, Order> :: isEmpty() const
{
	return (m_size == 0);
}

/*
* Insert method inserts the item at the correct spot in the list
* @param item to be inserted
* @return Iterator from inserted node
*/
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order> :: Iterator DLinkedOrderedList<Item, Order> :: insert(Item item) { 

	Node * current = m_head; /* current will be used as a temporary node used for storing nodes */
	/* First case: the list is empty, make a new tail = head with the value of the item */
	if (m_size == 0) 
	{
		m_tail = new Node(item, NULL, NULL);
		m_head = m_tail;
		m_size++;
		return Iterator(m_head, *this, FORWARD);
	}
	/* In this case our compare condition will pass if the new item has higher precedence then the head (which is current highest precedence item
	 * we create a new head with the item */
	else if (Order :: compare(item, m_head->value))
	{
		m_head = new Node(item, current, NULL);
		current->prev = m_head;
		m_size++;
		return Iterator(m_head, *this, FORWARD);
	}

	else 
	/* The last case is when the node is inserted anywhere but the front of the list, and has been broken down into two
	 * sub cases */
	{
		Node * newNode = new Node(item, NULL, NULL); /* new node to be inserted will NULL pointers, used for both sub cases */
		/* This checks to make sure we don't go to the tail */
		while (current->next != NULL)
		{
			current = current->next;
			/* item will be inserted before the compared node */
			if (Order :: compare(item, current->value)) 
			{
				/* Create links to the new node to keep ordering proper */
				Node* pre = current->prev;
				newNode->prev = pre;
				newNode->next = current;
				pre->next = newNode;
				current->prev = newNode;
				m_size++;
				return Iterator(newNode, *this, FORWARD); /* return iterator from inserted item */
			}
		}
		/* Handles case where we need to insert the new node as the tail. Return an iterator from the inserted node */
		current = m_tail;
		m_tail = newNode;
		newNode->prev = current;
		current->next = newNode;
		m_size++;
		return Iterator(newNode, *this, FORWARD);
	}
}

/*
* remove a specific item
* @return true if value is found
*/
template <class Item, class Order>
bool DLinkedOrderedList<Item, Order> :: remove(Item item)
{
	/* cannot find the item in the empty list */
	if (m_size == 0)
		return false;
	Node* oldNode = m_head; /* oldNode is the node used for traversing the list */
	/* Case 1, the item is at the head */
	if (m_head->value == item) 
	{
		m_head = m_head->next;
		m_head->prev = NULL;
		/* In case the head and the tail are the same node, null both pointers */
		if (m_head == NULL) 
			m_tail = NULL;
		m_size--;
		delete oldNode; /* delete the node we found */
		return true;
	}
	/* Case 2, item is not the head */
	else {
		while (oldNode != NULL) /* oldNode starts as head */
		{
			oldNode = oldNode->next;
			if (oldNode != NULL && oldNode->value == item) /* found the item to be removed */
				/* Case where tail needs to be removed */
				if (oldNode == m_tail)
				{
					m_tail = m_tail->prev;
					m_tail->next = NULL;
					m_size--;
					delete oldNode;
					return true;
				}
				else 
				/* Node is somewhere in the middle of the list. Need to fix links before and after oldNode before we delete it */
				{
					Node* pre = oldNode->prev;
					Node* post = oldNode->next;
					pre->next = post;
					post->prev = pre;
					m_size--;
					delete oldNode;
					return true;
				}
		}
	}
	/* item not found */
	return false;
}

/*
 * remove all removes all instances of item
 * @param item the item to be removed
 * @return the number of items removed
 */
template <class Item, class Order>
unsigned int DLinkedOrderedList<Item, Order> :: removeAll(Item item)
{
	unsigned int counter = 0;
	DLinkedOrderedList<Item, Order> :: Iterator itr = begin();
	while (itr.m_node->value != item)
	{
		++itr;
	}
	while (itr.m_node != NULL && itr.m_node->value == item)
	{
		remove(itr);
		counter++;
	}

	return counter;
}

/*
 * remove returns the removed item and increments the iterator that was passed in
 * @param iterator of the object to be removed
 * @return removed item
 */
template <class Item, class Order>
 Item DLinkedOrderedList<Item, Order> :: remove(Iterator& itr)
 {
	 Item retVal = *itr;
	 Node * current = itr.m_node;
	 ++itr;
	 if (m_head == m_tail)
	 {
		 m_head = NULL;
		 m_tail = NULL;
	 }
	 else if (current == m_head)
	 {
		 m_head = m_head->next;
		 m_head->prev = NULL;
	 }
	 else if (current == m_tail)
	 {
		m_tail = m_tail->prev;
		m_tail->next = NULL;
	 }
	 else 
	 {
		 Node * pre = current->prev;
		 Node * post = current->next;
		 pre->next = post;
		 post->prev = pre;
	 }
	 delete current;
	 m_size--;
	 return retVal;
 }

/*
 * begin function returns an iterator from the first node (depending on direction)
 * @param direction of iteration
 * @return an Iterator from the first node
 */
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order> :: Iterator DLinkedOrderedList<Item, Order> :: begin(Direction direction) 
{ 
	if (direction == FORWARD)
		return Iterator(m_head, *this, FORWARD);
	else return Iterator(m_tail, *this, BACKWARD);
}

/*
 * end function returns a NULL iterator to tell the program to stop iterating
 * @param direction of iteration
 * @return a NULL iterator
 */
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order> :: Iterator DLinkedOrderedList<Item, Order> :: end(Direction direction) 
{
	if (direction == FORWARD)
		return Iterator(NULL, *this, FORWARD);
	else return Iterator(NULL, *this, BACKWARD);
}

