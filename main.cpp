#include <iostream>
#include <stdlib.h>
#include "DLinkedOrderedList.h"
#include "StandardFunctors.h"
#include <assert.h>

using namespace std;

typedef DLinkedOrderedList<int>::Iterator itr; // equivalent to: typedef DLinkedOrderedList<int, IsLess>::Iterator
typedef DLinkedOrderedList<int, IsGreater>::Iterator itrG;
typedef DLinkedOrderedList<int, IsEqual>::Iterator itrE;

template<class Order>
void constructorCheck(DLinkedOrderedList<int, Order>& list){
	 // WILL CAUSE INTENTIONAL ILLEGAL MEMORY ACCESS IF DEFAULT CONSTRUCTOR IS NOT IDEAL
	if (list.begin() != list.end() || list.size()) { *(list.begin()); *(list.end()); }
}

template<class Order>
void fillList(DLinkedOrderedList<int, Order>& list, int lowerBound, int upperBound, int numEach = 1) {
	if (numEach < 1)  numEach = 1;
	if (numEach > 10) numEach = 10;
	if (upperBound < lowerBound) {
		lowerBound ^= upperBound; // XOR swap
		upperBound ^= lowerBound;
		lowerBound ^= upperBound;
	}
	for (int i = lowerBound; i < upperBound; i++) {
		for (int j = 0; j < numEach; j++) {
			list.insert(i);
		}
	}
}

template<class Order>
void printList(DLinkedOrderedList<int, Order>& list, Direction dir = FORWARD, char* txt = NULL) {
	if(txt) cout << txt;
	DLinkedOrderedList<int, Order>::Iterator i = list.begin(dir);
	for (; i != list.end(dir); ++i) {
		cout << *i << " ";
	}
	cout << endl << endl;
}

template <class Order>
void printTwoWays(DLinkedOrderedList<int, Order>& list) {
	DLinkedOrderedList<int, Order>::Iterator i = list.begin(), j = list.begin(BACKWARD);
	for (; i != list.end(); ++i, ++j){
		cout << *i << " " << *j << endl;
	}
	cout << endl;
}


void main(){

	// REMEMBER: F5, F10, and F11 are your friends.

	// DEFAULT CONSTRUCTOR AND COPY CONSTRUCTOR (FOR EMPTY-LIST-copies) CHECK
	DLinkedOrderedList<int> a;
	DLinkedOrderedList<int, IsGreater> b;

	constructorCheck(a); // program will INTENTIONALLY crash here if your DLinkedOrderedList default constructor is not perfect;
	constructorCheck(b); // do NOT use this function to test copy constructor on a DLOL which has a size > 0.

	DLinkedOrderedList<int> c(a);
	constructorCheck(c); // check if copy constructor works for empty DLOL  //WORKS


	// ORDERED INSERTION AND SIMULTANEOUS FORWARD/BACKWARD ITERATION CHECKS (uses overloaded dereference operator)
	fillList(a, 0, 10);
	cout << "size of a: " << a.size() << endl; // should print: size of a: 10
	printList(a, FORWARD, "Print of a: "); // should print:0 1 2 3 4 5 6 7 8 9  //WORKS
	printTwoWays(a); // should print:  //WORKS
	/*
	0 9
	1 8
	2 7
	3 6
	4 5
	5 4
	6 3
	7 2
	8 1
	9 0
	*/

	fillList(b, 0, 5, 2);
	printTwoWays(b); // should print:   //WORKS
	/*
	4 0
	4 0
	3 1
	3 1
	2 2
	2 2
	1 3
	1 3
	0 4
	0 4
	*/
	
	// remove(Iterator&) test
	a.remove(a.begin()); // should remove '0'
	a.remove(a.begin()); // should remove '1'

	// remove(Item) test
	cout << "a.remove(3): " <<       (a.remove(3)?"TRUE":"FALSE") << endl; // should print 'TRUE'
	cout << "a.remove(3) again: " << (a.remove(3)?"TRUE":"FALSE") << endl; // should print 'FALSE' 
	a.remove(6);
	printList(a, BACKWARD, "Backward print of a: "); // should print:9 8 7 5 4 2   //WORKS

	
	// removeAll test
	DLinkedOrderedList<int> d;
	d.insert(5); d.insert(6); d.insert(6);

	cout << d.removeAll(6) << " 6's removed from d." << endl << endl; // should print "2 6's removed from d."  

	printList(d, FORWARD, "Remaining elements in d: "); // should print: 5  //WORKS


	// TEST NON-ZERO LIST WITH COPY CONSTRUCTOR
	DLinkedOrderedList<int> e(a);
	cout << "Copy constructor +\nForward print of e: ";
	printList(e); // should print:0 1 3 4 5 7 8 9 (reverse of backward print of a)  //WORKS //prints 2 4 5 7 8 9 

	DLinkedOrderedList<int> f;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			f.insert(5);
		}
		cout << "removed: " << f.removeAll(5);
		cout << ". Is empty? " << (f.isEmpty()?"TRUE":"FALSE") << endl; // should print "removed: 5. Is empty? TRUE" 3 times
	}
	cout << endl;

	printList(f, FORWARD, "Nothing should print after this arrow: ->"); // nothing on the same line after the arrow, that is.

	DLinkedOrderedList<int, IsEqual> g;
	fillList(g, 0, 10);
	// output will vary with how you wrote your 'insert()' function.
	// However, all values should be in ascending or descending order.
	printList(g, FORWARD, "g List: ");

	// test Iterator kill function
	for (itrE k = g.begin(); k != g.end();) {
		k.kill(); // increment operator called somehow in this or another function
	}
	cout << "Nothing should print after this arrow: ->";
	printList(g);

	g.insert(1);
	g.insert(4);
	g.insert(6);
	
	itrE k=g.begin();
	cout<<*k<<endl;  //should print 1
	cout<<*(++k)<<endl; //should print 4
	cout<<*(++k)<<endl; //should print 6
	cout<<*(--k)<<endl; //should print 4

	k.kill();
	cout<<*k<<endl;//should print 6


	cout<<*(--k)<<endl; //should print 1   *****************

	cin.ignore();
}