/* Gregory Wicklund
* Class: CSCI-2421
* HW 6 dictionary.cpp file
*/

#include <iostream>
#include <string>
#include <list>
#include "DictEntry.h"
#include "dictionary.h"

using namespace std;

dictionary::dictionary()
{
	; //Leaving blank
}

//Forward and backward searches function virtually identically, the only difference is where in the list they search
int dictionary::searchForward(list<DictEntry>& wordList, wordType& findString)
{
	//Set a search counter
	int searches = 0;
	//Search from the start of the list to the end
	for (list<DictEntry>::iterator iter = wordList.begin(); iter != wordList.end(); iter++)
	{
		//Increment searches
		searches++;
		//If the word is found, return the current value of searches
		if (iter->getWord() == findString)
			return(searches);
	}
	//If the code gets here, the search term is not in the list, return -1 to indicate this.
	return(-1);
}

int dictionary::searchBackward(list<DictEntry>& wordList, wordType& findString)
{
	int searches = 0;
	for (list<DictEntry>::reverse_iterator iter = wordList.rbegin(); iter != wordList.rend(); iter++)
	{
		searches++;
		if (iter->getWord() == findString)
			return(searches);
	}
	return(-1);
}

void dictionary::revPrintList(ostream& output, list<DictEntry> &wordList)
{
	//Iterate from the end of the list to the start, print each entry.
	for (list<DictEntry>::reverse_iterator iter = wordList.rbegin(); iter != wordList.rend(); iter++)
	{
		output << iter->getWord() << ' ';
	}
}