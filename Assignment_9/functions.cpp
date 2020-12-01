/* Gregory Wicklund
* Class: CSCI-2421
* HW 9 functions.cpp file
*/

//Functions file to create a hash, make strings lowercase, and strip punctuation.
#include <string>

using namespace std;

string makeLower(string word)
{
	string temp = "";
	for (unsigned int i = 0; i < word.length(); i++)
	{
		temp += tolower(word[i]);
	}
	return(temp);
}

string removePunct(string word)
{
	for (unsigned int i = 0; i < word.size(); i++) //Relying on it auto-resizing
	{
		if (!isalnum(word[i]) && (word[i] != '\''))
		{
			word.erase(i--, 1);
		}
	}
	return(word);
}

unsigned int hashGen(string word)
{
	//Declare hash and unsigned int
	hash<string> hashStr;
	unsigned int h;

	//Hash the passed string
	h = hashStr(word);

	//Return the hash modulo 1373, to match the number of buckets we're working with.
	return(h % 1373);
}