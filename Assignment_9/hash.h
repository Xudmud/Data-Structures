/* Gregory Wicklund
* Class: CSCI-2421
* HW 9 hash.h file
*/

#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <list>
//#include <fstream>

using namespace std;

class Hash
{
private:
	list<string> hashlist[1373];

public:
	Hash();
	void addWord(string);
	int spellCheck(string);
};

#endif