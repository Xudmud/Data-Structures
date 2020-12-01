/* Gregory Wicklund
* Class: CSCI-2421
* HW 3 Recursive.h file
*/

#ifndef RECURSIVE
#define RECURSIVE

#include <string>
#include <vector>

class Recursive
{
public:
	//Declare functions. Declaring as static so main.cpp can access them.
	//Overloaded recursive functions (int for year, 1 string for model, 2 strings for make)
	static int searchRec(int, const std::vector<Vehicle>&,int,int,int);
	static int searchRec(std::string, const std::vector<Vehicle>&,int,int,int);
	static int searchRec(std::string, std::string, const std::vector<Vehicle>&,int,int,int);

	//Overloaded iterative functions (same rules as recursive)
	static int searchIter(int&, const std::vector<Vehicle>&);
	static int searchIter(std::string, const std::vector<Vehicle>&);
	static int searchIter(std::string, std::string, std::vector<Vehicle>&);

	
};

#endif