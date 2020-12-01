/* Gregory Wicklund
* Class: CSCI-2421
* HW 5 LinkedList.cpp file
*/

#include "LinkedList.h"
#include <iostream>

//Functions
LinkedList::LinkedList()
{
	headPtr = new Node;
	headPtr->nextPtr = nullptr;
	headPtr->data = ' ';
}

LinkedList::~LinkedList()
{

}

//Code taken from the in-class example
bool LinkedList::insertAtFront(char value)
{
	//create a new node
	Node * newNode = new Node;

	//fill the new node with data
	newNode->data = value;

	//connect new node to what head pointer points to
	newNode->nextPtr = headPtr->nextPtr;
	//connect head pointer to new node
	headPtr->nextPtr = newNode;
	return(true);
}


bool LinkedList::insertBeforePosition(char value, int index)
{

	int position = 0;
	//create a new node
	Node* newNode = new Node;
	Node* tmpNode = headPtr;

	//fill the new node with data
	newNode->data = value;

	//Connect the new node to the appropirate position.
	for (int i = 0; i < index; i++)
	{
		if (tmpNode->nextPtr == nullptr)
			return(false);
		tmpNode = tmpNode->nextPtr;
	}
	newNode->nextPtr = tmpNode->nextPtr;
	tmpNode->nextPtr = newNode;
	return(true);
	
}

bool LinkedList::insertAtBack(char value)
{
	int size = 0;
	//create a new node
	Node* newNode = new Node;
	Node* ptr = headPtr;
	//fill the new node with data
	newNode->data = value;
	//Check if next pointer is null
	if (ptr->nextPtr == nullptr)
	{
		headPtr->nextPtr = newNode;
		newNode->nextPtr = nullptr;
		return(true);
	}
	//Temporarily assign newNode to headptr's next.
	//This should equate to nullptr.
	newNode->nextPtr = headPtr->nextPtr;
	//Traverse the list to the end
	while (ptr->nextPtr != nullptr)
	{
		size++;
		ptr = ptr->nextPtr;
	}

	ptr->nextPtr = newNode;
	//connect node to nullptr
	newNode->nextPtr = nullptr;
	//Check if it's the only item.
	

	//connect the list to the node
	return(true);
}

bool LinkedList::deleteAtFront()
{
	Node* temp = headPtr;
	//point headptr to the node after the one it's pointing at
	//headPtr->nextPtr = headPtr->nextPtr->nextPtr;
	headPtr = headPtr -> nextPtr;
	//delete the first entry
	delete temp;
	
	//order matters, or you lose access to the whole thing.
	return(true);
}

bool LinkedList::deletePosition(int index)
{
	//traverse to the index
	Node* temp = headPtr->nextPtr;
	for (int i = 1; i < index; i++)
		temp = temp->nextPtr;
	//New temporary node at the one to be removed
	Node* temp2 = temp->nextPtr;
	//Point temp to the node after, unless it's at the end.
	if (temp->nextPtr != nullptr)
		temp->nextPtr = temp->nextPtr->nextPtr;
	else
		temp->nextPtr = nullptr;
	//delete the old node
	delete temp2;
	return(true);
}

bool LinkedList::deleteAtBack()
{
	Node* tempPtr = headPtr;
	//Traverse list to the second-to-last item.
	while (tempPtr->nextPtr->nextPtr != nullptr)
	{
		tempPtr = tempPtr->nextPtr;
	}
	//Create link to last item
	Node* tempPtr2 = tempPtr->nextPtr;
	//Next object of tempPtr is nullptr.
	tempPtr->nextPtr = nullptr;
	//Delete last item
	delete tempPtr2;
	return(true);
}

std::ostream& operator << (std::ostream& out, LinkedList list)
{
	Node* ptr = list.headPtr->nextPtr;
	std::cout << "";
	while (ptr != nullptr)
	{
		if (ptr->nextPtr == nullptr)
		{
			out << ptr->data << "";
		}
		else
		{
			out << ptr->data << "";
		}
		ptr = ptr->nextPtr;
	}
	return out;
}

LinkedList operator +(LinkedList& list1, LinkedList& list2)
{
	LinkedList templist;
	Node* tempNode = list1.headPtr;
	while (tempNode->nextPtr != nullptr)
	{
		tempNode = tempNode->nextPtr;
		templist.insertAtBack(tempNode->data);
		
	}

	tempNode = list2.headPtr;
	while (tempNode->nextPtr != nullptr)
	{
		tempNode = tempNode->nextPtr;
		templist.insertAtBack(tempNode->data);
		
	}
	return(templist);
}

LinkedList operator -(LinkedList& list1, LinkedList& list2)
{
	LinkedList templist = list1;
	
	Node* tempNode = list2.headPtr->nextPtr;
	while (tempNode != nullptr)
	{
		int pos = 1;
		bool found = false;
		Node* tempNode2 = list1.headPtr->nextPtr;
		while (tempNode2->nextPtr != nullptr && !found)
		{
			if (tempNode2->data == tempNode->data)
			{
				templist.deletePosition(pos);
				found = true;
			}
			else
			{
				pos++;
				tempNode2 = tempNode2->nextPtr;
			}
		}
		tempNode = tempNode->nextPtr;
	}
		//Temp node for list1
		//Traverse templist to its end.
		//Check equality at each point
		//If equal, remove entry
		
	return(templist);
}
