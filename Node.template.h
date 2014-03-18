/************************************************************************/
/* Class node creates nodes to be used for storing items in the doubly linked list
* @author Eric Stevenson (using provided header files from CS1037a*/
/************************************************************************/

/*
* Node constructor
* @param val type Item, default creates new Item
* @param _next is a pointer to the next node (default NULL)
* @param _previous is a pointer to the previous node (default NULL)
*/
template <class Item, class Order>
DLinkedOrderedList<Item, Order> :: Node :: Node(Item val, Node* _next, Node* _prev): value(val), next(_next), prev(_prev) {}


