/* Gregory Wicklund
* Class: CSCI-2421
* HW 5 main.cpp file
*/
#include <iostream>
#include <fstream>
#include "LinkedList.h"

using namespace std;


int main()
{
	char c;
	ifstream fin;
	fin.open("input.txt");
	if (fin.fail())
	{
		cout << "Unable to open input file.";
		exit(1);
	}
	LinkedList list;
	LinkedList list2;
	LinkedList list3;
	LinkedList list4;
	//Grab the initial character
	c = fin.get();
	do
	{
		if(c != '\n')
			list.insertAtBack(c);
		c = fin.get();
	} while (!fin.eof() && c != '\n');
	//Need this once more or I miss a character
//	c = fin.get(); //Clear the newline character.
	do
	{
		if (c != '\n')
			list2.insertAtBack(c);
		c = fin.get();
	} while (!fin.eof() && c != '\n');
	list3 = list + list2;
	cout << list3 << endl;
	list4 = list - list2;
	cout << list4 << endl;
	fin.close();
	return(0);
}

