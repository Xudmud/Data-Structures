/* Gregory Wicklund
* Class: CSCI-2421
* HW 5 LinkedList.h file
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

//This can't be in its own header apparently.
struct Node
{
	char data;
	Node* nextPtr;
};


class LinkedList
{
private:
	Node* headPtr;

public:
	LinkedList();
	~LinkedList();
	bool insertAtFront(char value);
	bool insertBeforePosition(char value, int index);
	bool insertAtBack(char value);
	bool deleteAtFront();
	bool deletePosition(int index);
	bool deleteAtBack();
	friend std::ostream& operator << (std::ostream& out, LinkedList list);
	friend LinkedList operator + (LinkedList&, LinkedList&);
	friend LinkedList operator - (LinkedList&, LinkedList&);
};

#endif
