/* Gregory Wicklund
* Class: CSCI-2421
* HW 6 main.cpp file
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "DictEntry.h"
#include "dictionary.h"

using namespace std;

int main()
{
	//Declare variables and streams
	ifstream wordsin;
	ifstream searchin;
	ofstream fout;
	string holder;
	DictEntry temp;
	dictionary dict;
	list<DictEntry> words;

	//Open the word input file
	wordsin.open("dictionary.txt");
	if (!wordsin.is_open())
	{
		cout << "Could not open input file." << endl;
		exit(1);
	}
	//Open the search input file
	searchin.open("findwords.txt");
	if (!searchin.is_open())
	{
		cout << "Could not open search file." << endl;
		//close the input file, since it did open.
		wordsin.close();
		exit(2);
	}

	//Read in words, one at a time.
	while (!wordsin.eof())
	{
		//Get word
		getline(wordsin, holder);
		temp.setWord(holder);
		/*	//Get definition. Keeping this commented here to show it would function if needed. 
		 *	getline(wordsin, holder);
		 *	temp.setDef(hodler);*/

		//add the new element to the list.
		words.emplace_back(temp);
	}

	//Sort the list alphabetically by word.
	words.sort();

	cout << "Searching for each word in the search file, from the beginning of the list." << endl;
	while (!searchin.eof())
	{
		string searchterm;
		int searches = 0;
		getline(searchin, searchterm);
		searches = dict.searchForward(words, searchterm);
		cout << searchterm << ": ";
		if (searches == -1)
		{
			cout << words.size() << " iterations (word not found)" << endl;
		}
		else
		{
			cout << searches << " iterations" << endl;
		}
	}

	//close the input file
	searchin.close();

	searchin.open("findwords.txt");
	if (!searchin.is_open()) //the file should open, but guard against it not for some reason.
	{
		cout << "Could not open file for searching." << endl;
		wordsin.close();
		exit(3);
	}
	cout << "\nSearching for each word in the search file, from the end of the list." << endl;
	while (!searchin.eof())
	{
		string searchterm;
		int searches = 0;
		getline(searchin, searchterm);
		searches = dict.searchBackward(words, searchterm);	 
		cout << searchterm << ": ";
		if (searches == -1)
		{
			cout << words.size() << " iterations (word not found)" << endl;
		}
		else
		{
			cout << searches << " iterations" << endl;
		}
	}
	searchin.close(); //we're done with this file now.

	fout.open("revsort.txt");
	dict.revPrintList(fout, words);
	cout << "\nWrote a reverse sorted list to revsort.txt" << endl;

	//close open files
	wordsin.close();



	return(0);
}