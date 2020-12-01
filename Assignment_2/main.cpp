/* Gregory Wicklund
 * Class: CSCI-2421
 * HW 2 main.cpp file
 */

#include "ArrayBag.h"
#include <iostream>
#include <fstream>
#include <string> //dunno if I need this?
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	//Open streams and files
	stringstream ss;
	ifstream fin;
	//ofstream fout; //Could implement writing results to a file declared by ostream.
	fin.open("setInput.txt");
	if(!fin.is_open()) //Check to make sure file actually loaded.
	{
		cout << "Cannot find input file." << endl;
		return(1);
	}

	//Declare ArrayBag variables.
	ArrayBag bag1;
	ArrayBag bag2;
	ArrayBag bagComb;
	ArrayBag bagDiff;

	//boolean to ensure inputs were read
	bool addSuccess;

	//read inputs from input file. Reads two lines, any additional lines are ignored.
	string ints1, ints2;
	getline(fin, ints1);
	getline(fin, ints2);
	ss << ints1;

	//Add the line read to an ArrayBag.
	addSuccess = bag1.addItems(ss, bag1);
	if(!addSuccess)
	{
		return(2); //defining exit code of 2 for an invalid input.
	}
	ss.clear(); //Clear stream for next line.
	ss << ints2;
	addSuccess = bag2.addItems(ss, bag2);
	if(!addSuccess)
	{
		return(2);
	}
	ss.clear();

	//Demonstrate overloaded + and - operators.
	bagComb = bag1 + bag2;
	bagDiff = bag1 - bag2;


	//Print ArrayBag contents. 
	cout << "Bag 1 contents: " << endl;
	bag1.printBag();
	cout << "Bag 2 contents: " << endl;
	bag2.printBag();
	cout << "bag 1 + bag 2: " << endl;
	bagComb.printBag();
	cout << "bag 1 - bag 2: " << endl;
	bagDiff.printBag();

	fin.close();
	return(0);
}