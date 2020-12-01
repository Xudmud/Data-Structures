/* Gregory Wicklund
* Class: CSCI-2421
* HW 7 main.cpp file
*/

#include <queue>
#include <fstream>
#include <iostream>
#include <vector>
#include "Bank.h"

using namespace bankqueue;
using namespace std;

int main()
{
	ifstream fin;
	//int numCustomers = 0;
	//int currentTime = 0;
	fin.open("patrons.txt");
	Bank bankline;
	
	bankline.readPatrons(fin);
	bankline.process();
	bankline.printResults();
	return(0);

}