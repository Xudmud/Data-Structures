/* Gregory Wicklund
* Class: CSCI-2421
* HW 9 hash.cpp file
*/

#include "hash.h"
#include "functions.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Hash::Hash() //Constructor
{
	//intentionally empty, the list shoud be initialized with empty containers.
}

void Hash::addWord(string word)
{
	word = removePunct(word);

	word = makeLower(word);
	
	//Generate the word hash
	unsigned int h = hashGen(word);

	//Add the hashed word to the appropriate bucket
	hashlist[h].push_back(word);
}

int Hash::spellCheck(string word)
{
	word = removePunct(word);
	word = makeLower(word);
	if (word == "")
	{
		//If the "word" was just punctuation (e.g. "--") then there's no need to check against the hash table.
		return(-1);
	}
	//Generate the passed string's hash
	unsigned int h = hashGen(word);

	//Check against the hash bucket.
	for (list<string>::iterator i = hashlist[h].begin(); i != hashlist[h].end(); i++)
	{
		//In looking for a suitable way to get to the data from the pointer, VS had the data() method as an option.
		//I tried using it and it happened to work without a hitch.
		if (i->data() == word)
			return(0); //word is found, and thus spelled correctly
	}
	return(1); //Gone through the hash list, word is not spelled correctly.

}

