/* Gregory Wicklund
 * Class: CSCI-2421
 * HW 4 main.cpp file
 */

//per homework instructions, no includes for <vector> or <algorithm>
#include "MyVector.h"
#include <iostream>
#include <cstdlib> //rand() and time()

using namespace std;

//Function to print current vector contents
void printVector(HW4::MyVector);


int main(int argc, char* argv[])
{
	//Seed RNG
	srand(time(NULL));

	//Declare variables
	HW4::MyVector first;
	int value; //for search
	char again;
	
	//Show pop_back() will not remove anything if the vector is already empty.
	cout << "Demonstrating that pop_back() will not remove an entry from an empty vector." << endl;
	first.pop_back();

	//Demonstrating push_back(). Add 20 random values to the vector.
	cout << "Demonstrating push_back(): Adding 20 random integers. from 0 to 20\n";
	for(int i = 0; i < 10; i++)
	{
		first.push_back(rand() % 21);
	}

	//Print current vector. (function? Pass vec object?)
	printVector(first);

	//demonstrate pop_back()
	cout << "Demonstrating pop_back(). Removing the last integer.\n";
	first.pop_back();
	printVector(first);

	//Add two more values, to show the array is still functioning.
	cout << "Re-adding an additional two values.\n";
	first.push_back(rand() % 21);
	first.push_back(rand() % 21);
	printVector(first);

	//demonstrate search()
	cout << "Demonstrating search.\n";
	do
	{
		int index = -1;
		cout << "Please enter an integer to search: ";
		cin >> value;
		if (cin.fail())
		{
			cout << "You did not enter an integer.\n";
			//The while loop exits as it is if this code gets executed, I think it's keeping the input stream for the next prompt.
			return(1);
		}
		else
		{
			index = first.search(value);
		}
		if (index == -1)
		{
			cout << "The search term was not found in the vector.\n";
		}
		else
		{
			cout << "Found your search at index " << index << ".\n";
		}
		cout << "Do you want to search again? (y/n): ";
		cin >> again;
	} while (again == 'y' || again == 'Y');
	
	return(0);
}

void printVector(HW4::MyVector first)
{
	cout << "The vector now has " << first.size() << " elements: \n[ ";
	for (int i = 0; i < first.size(); i++)
	{
		cout << first[i] << ' ';
	}
	cout << "]\n\n" << endl;
}