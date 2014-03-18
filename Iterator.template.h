/************************************************************************/
/* Class Iterator allows for easy traversal of list
* @author Eric Stevenson (using header file from CS 1037 */
/************************************************************************/

/*
* Constructor creates iterator, default direction is forward
*/
template <class Item, class Order>
DLinkedOrderedList<Item, Order> :: Iterator :: Iterator(
	Node* const node,
	DLinkedOrderedList<Item, Order>& list,
	Direction direction) : m_node(node), m_list(list) ,m_direction(direction){}

/*
* Operator++ method provides ability to access to next nodes. 
* @return the next (or previous if direction is backwards) node
*/
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order> :: Iterator& DLinkedOrderedList<Item, Order> :: Iterator :: operator++() {
	if (m_direction == 1)
		m_node = m_node->next;
	else 
		m_node = m_node->prev;
	return *this;
}

/*
* Operator-- method provides ability to access previous nodes. 
* @return the next (or previous if direction is backwards) node
*/
template <class Item, class Order>
typename DLinkedOrderedList<Item, Order> :: Iterator& DLinkedOrderedList<Item, Order> :: Iterator :: operator--() 
{
	if (m_direction == 1)
		m_node = m_node->prev;
	else 
		m_node = m_node->next;
	return *this;
}

/*
*operator != method answers the question, Does "this" NOT point to the same node as "b"?
*@return true if above question would be answered true
*@param Iterator to be compared to
*/
template <class Item, class Order>
bool DLinkedOrderedList<Item, Order> :: Iterator :: operator!=(Iterator const& b) const
{
	return (b.m_node != m_node);
}
/*
* Operator * lets us access the value at a node
* 
*/
template <class Item, class Order>
Item& DLinkedOrderedList<Item, Order> :: Iterator :: operator*() const
{
	return m_node->value;
}

/*
* kill method deletes an item and increments the iterator
* @return the item removed
*/
template <class Item, class Order>
Item DLinkedOrderedList<Item, Order> :: Iterator :: kill()
{
	return m_list.remove(*this);
}