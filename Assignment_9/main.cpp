/* Gregory Wicklund
* Class: CSCI-2421
* HW 9 main.cpp file
*/

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "hash.h"
#include "functions.h"

using namespace std;
int main()
{
	//Create the hash object
	Hash wordHash;

	//Declare streams for dictionary, check file, and output file.
	ifstream dictfin;
	ifstream checkfin;
	ofstream fout;
	
	//Declare variables for the current word, word counts, and filenames.
	string str;
	int dictCount = 0;
	int checkCount = 0;
	int missCount = 0;
	string dictFile;
	string checkFile;
	bool foutgood;

	cout << "Please enter a dictionary file: ";
	//Using getline instead of cin in case the filename has spaces.
	getline(cin, dictFile);
	dictfin.open(dictFile);
	if (dictfin.fail())
	{
		cout << "Failed to open dictionary file. Stopping." << endl;
		exit(1);
	}
	while (dictfin >> str)
	{
		wordHash.addWord(str);
		dictCount++;
	}
	//We're done with the dictionary file, so close it. Another dictionary file could be passed if needed.
	dictfin.close();

	cout << "Please enter a text file to spell check: ";
	getline(cin, checkFile);
	checkfin.open(checkFile);
	if (checkfin.fail())
	{
		cout << "Failed to open file to spell check. Stopping." << endl;
		exit(2);
	}
	//Open output file specific to the given check file.
	fout.open("results_" + checkFile);
	if (fout.fail())
	{
		int cont;
		//Set foutgood to false, program will instead print to stdout.
		foutgood = false;
		//Considering how much output there is, prompt user before starting output to stdout.
		cout << "Failed to open output file; falling back to stdout. Continue, or exit?\n";
		cout << "1. Continue\n"
			<< "2. Exit\n";
		cin >> cont;
		//If 1 is not given, assume the user wants to exit.
		if (cont != 1)
		{
			cout << "Stopping program." << endl;
			exit(3);
		}
	}
	else
	{
		foutgood = true;
	}
	while (checkfin >> str)
	{
		checkCount++;
		int check = wordHash.spellCheck(str);
		if(check != -1) //Ignoring "words" that contain no letters or numbers
		{
			if (check == 1)
				//Remove punctuation and make lowercase
			{
				missCount++;
				str = removePunct(str);

				//Output to either stdout or fout
				if (foutgood)
					fout << str << endl;
				else
					cout << str << endl;
			}
		}
	}
	if (foutgood)
	{
		fout << "Number of words in dictionary: " << dictCount << endl
			<< "Number of words in check file: " << checkCount << endl
			<< "Number of misspelled words: " << missCount << endl;
		cout << "Done. Please see results_" << checkFile << " for the results." << endl;
	}
	else
		cout << "Number of words in dictionary: " << dictCount << endl
			<< "Number of words in check file: " << checkCount << endl
			<< "Number of misspelled words: " << missCount << endl;

	//We're done with the spell check file and results file, so close them.
	checkfin.close();
	fout.close();


	return(0);
}