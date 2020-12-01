/* Gregory Wicklund
* Class: CSCI-2421
* Final Project MenuFunctions.cpp file
*/

/* MenuFunctions.cpp file
	Contains the main menu flow and most menu dialogs the user may encounter.*/

#include "MenuFunctions.h"
#include "ActorFunctions.h"
#include "ActorActress.h"
#include "BSTreeActor.h"
#include "NodeActor.h"
#include "Picture.h"
#include "PictureFunctions.h"
#include "BSTreePicture.h"
#include "NodePicture.h"
#include <iostream>
#include <string>
using namespace std;

void mainMenu()
{
	//Declare new binary search trees
	BSTreeActor* treeAct = new BSTreeActor;
	BSTreePicture* treePict = new BSTreePicture;

	//Declare vectors to hold search results and sorted fields
	vector<Actor> searchResultsActor;
	vector<Actor> sortedActors;
	vector<Picture> searchResultsPicture;
	vector<Picture> sortedPictures;

	while (true)
	{
		switch (displayMainOptions())
		{
		//Read in data from file.
		case 1:
			cout << "\nReading in from file.";
			switch (displayDataTypeOptions())
			{
			case 1:
				readActorsIn(getFileNameChoice(), treeAct);
				//set actorRead to true, since we've read the file in.
				break;
			case 2:
				//Similar to case 1, but for the pictures file.
				readPicturesIn(getFileNameChoice(), treePict);
				break;
			default:
				//This code should never run, but just in case.
				cout << "Invalid option entered.\n" << endl;
			} //

			break;
		//Search data for specific keyword
		case 2:
			cout << "\nSearching for keyword.";
			switch (displayDataTypeOptions())
			{
			case 1:
				searchResultsActor = searchActor(treeAct);
				break;
			case 2:
				searchResultsPicture = searchPicture(treePict);
				break;
			} //end switch(chooseElementRead())
			break;
		//Add data to file
		case 3:
			//Function for adding node to a tree.
			cout << "\nAdding to database.";
			switch (displayDataTypeOptions())
			{
			case 1:
				addActorNode(treeAct);
				break;
			case 2:
				addPictureNode(treePict);
				break;
			}
			break;
		//Delete data from file
		case 4:
			//Use search function, get results.
			//For each delete (if any), search based off
			//key and delete node.
			//Limitation: no way to undo.
			cout << "\nRemoving from database.";
			switch (displayDataTypeOptions())
			{
			case 1:
				deleteActorNode(treeAct);
				break;
			case 2:
				deletePictureNode(treePict);
				break;
			}
			break;
		//Modify data
		case 5:
			cout << "\nModifying data.";
			switch (displayDataTypeOptions())
			{
			case 1:
				modifyActorData(treeAct);
				break;
			case 2:
				modifyPictureData(treePict);
				break;
			}
			break;
		
		//Sort data
		case 6:
			cout << "\nSorting data.";
			switch (displayDataTypeOptions())
			{
			case 1:
				switch (displayDataSourceOptions())
				{
				//Full tree
				case 1:
					sortedActors = sortActors(treeAct);
					break;
				//Search results
				case 2:
					sortedActors = sortActors(searchResultsActor);
					break;
				case 3:
					sortedActors = sortActors(sortedActors);
					break;
				default:
					cout << "Invalid input given. Returning to main menu.\n" << endl;
				} //switch
				break;
			case 2:
				switch (displayDataSourceOptions())
				{
				case 1:
					sortedPictures = sortPictures(treePict);
					break;
				case 2:
					sortedPictures = sortPictures(searchResultsPicture);
					break;
				case 3:
					sortedPictures = sortPictures(sortedPictures);
				} //switch
				break;
			}
			break;
		//Save current data to file
		case 7:
			cout << "\nWriting data to file";
			//Function to write data to file, either same or new.
			//Source for bool-flipping: https://stackoverflow.com/questions/610916/easiest-way-to-flip-a-boolean-value
			switch (displayDataTypeOptions())
			{
			case 1:
				switch (displayDataSourceOptions())
				{
				case 1:
					printActorsToFile(treeAct);
					break;
				case 2:
					printActorsToFile(searchResultsActor);
					break;
				case 3:
					printActorsToFile(sortedActors);
					break;
				} //switch
				break;
			case 2:
				switch (displayDataSourceOptions())
				{
				case 1:
					printPicturesToFile(treePict);
					break;
				case 2:
					printPicturesToFile(searchResultsPicture);
					break;
				case 3:
					printPicturesToFile(sortedPictures);
					break;
				} //switch
				break;
			}
			break;
		case 8:
			return; //exit the loop, since the user is done.
			break;
		default:
			cout << "Invalid option given." << endl;
		} //end switch(displayOptions())
	} //end while(true)
}

int displayMainOptions()
{
	int option = -1;
	while (option < 1 || option > 8)
	{
		cout << "\nPlease choose an option:\n"
			<< "1. Read in data from files\n"
			<< "2. Search data for specific keyword\n"
			<< "3. Add data to file\n"
			<< "4. Delete data from file\n"
			<< "5. Modify data\n"
			<< "6. Sort Data\n"
			<< "7. Save current data to file.\n"
			<< "8. Exit" << endl;
		cout << "Choose an option: ";
		cin >> option;
		if (option < 1 || option > 8)
			cout << "Invalid option given, please try again." << endl;
	}
	return(option);
}

//Source for breaking choices into their own functions (which should have been common sense)
//https://stackoverflow.com/questions/14669457/initialization-of-element-is-skipped-by-case-label
int displayDataTypeOptions()
{
	int option1 = -1;
	while (option1 != 1 && option1 != 2)
	{
		cout << "\nWhich kind of data?\n"
			<< "1. Actors/Actresses\n"
			<< "2. Pictures" << endl;
		cout << "Choose an option: ";
		cin >> option1;
		if (option1 != 1 && option1 != 2)
		{
			cout << "Invalid option entered. Please try again.\n" << endl;
		}
	}
	return(option1);
}

int displayActorSearchOptions()
{
	int optionSearch = -1;
	while (optionSearch < 1 || optionSearch > 5)
	{
		cout << "Search by which field?\n"
			<< "1. Actor/Actress Name\n"
			<< "2. Film Title\n"
			<< "3. Award Name\n"
			<< "4. Year of Release\n"
			<< "5. Won/Lost Award\n" << endl;
		cout << "Please choose an option: ";
		cin >> optionSearch;
		if (optionSearch < 0 || optionSearch > 5)
		{
			cout << "Invalid option given. Please try again.\n" << endl;
		}
	}
	return(optionSearch);
}

int displayPictureSortOptions()
{
	int optionSort = -1;
	while (optionSort < 1 || optionSort > 10)
	{
		cout << "Sort by which field?\n"
			<< "1. Picture Name\n"
			<< "2. Month of Release\n"
			<< "3. Year of Release\n"
			<< "4. Film Duration\n"
			<< "5. Number of Nominations\n"
			<< "6. Genre 1\n"
			<< "7. Genre 2\n"
			<< "8. Film Rating (0-100)\n"
			<< "9. Metacritic Score\n"
			<< "10. Synopsis" << endl;
		cout << "Please choose an option: ";
		cin >> optionSort;
		if (optionSort < 1 || optionSort > 10)
		{
			cout << "Invalid option entered. Please try again\n" << endl;
		}
	}
	return(optionSort);
}

int displayActorWinLoseOptions()
{
	int optionSearch = -1;
	while (optionSearch < 1 || optionSearch > 2)
	{
		cout << "Won or lost award?\n"
			<< "1. Won\n"
			<< "2. Lost" << endl;
		cout << "Choose an option: ";
		cin >> optionSearch;
		if (optionSearch < 1 || optionSearch > 2)
		{
			cout << "Invalid option given. Please try again\n" << endl;
		}
	}
	return(optionSearch);
}

int displayModifyPictureOptions()
{
	int optionModify = -1;
	while (optionModify < 1 || optionModify > 11)
	{
		cout << "Modify which field? Please choose one at a time.\n"
			<< "1. Picture Name\n"
			<< "2. Month of Release\n"
			<< "3. Year of Release\n"
			<< "4. Film Duration\n"
			<< "5. Number of Nominations\n"
			<< "6. Genre 1\n"
			<< "7. Genre 2\n"
			<< "8. Film Rating (0-100)\n"
			<< "9. Metacritic Score\n"
			<< "10. Synopsis"
			<< "11. Return" << endl;
		cout << "Please choose an option: ";
		cin >> optionModify;
		if (optionModify < 1 || optionModify > 11)
		{
			cout << "Invalid option entered. Please try again\n" << endl;
		}
	}
	return(optionModify);
}

int displayPartialCompleteOptions()
{
	int optionSearchPC = -1;
	while (optionSearchPC != 1 && optionSearchPC != 2)
	{
		//This function can be used for any search that requires a choice of partial or complete.
		cout << "Complete or Partial search?\n"
			<< "1. Complete\n"
			<< "2. Partial" << endl;
		cout << "Enter a choice: ";
		cin >> optionSearchPC;
		if (optionSearchPC != 1 && optionSearchPC != 2)
		{
			cout << "Invalid option entered. Please try again.\n" << endl;
		}
	}
	return(optionSearchPC);
}

int displaySearchWithinResultsOptions()
{
	int optionSearch = -1;
	while (optionSearch < 1 || optionSearch > 2)
	{

		cout << "Search within results?\n"
			<< "1. Yes\n"
			<< "2. No" << endl;
		cout << "Please choose an option: ";
		cin >> optionSearch;
		if (optionSearch < 1 || optionSearch > 2)
		{
			cout << "Invalid option given. Please try again\n" << endl;
		}
	}
	return(optionSearch);
}

int displayActorSortOptions()
{
	int optionSort = -1;
	while (optionSort < 1 || optionSort > 5)
	{
		cout << "Sort by which field?\n"
			<< "1. Actor/Actress Name\n"
			<< "2. Film Title\n"
			<< "3. Award Name\n"
			<< "4. Year\n"
			<< "5. Won/Lost Award" << endl;
		cout << "Please choose an option: ";
		cin >> optionSort;
		if (optionSort < 1 || optionSort > 5)
		{
			cout << "Invalid option entered. Please try again\n" << endl;
		}
	}
	return(optionSort);
}

int displayActorOutputOptions()
{
	int optionOutput = -1;
	while (optionOutput < 1 || optionOutput > 6)
	{
		cout << "Select fields, one at a time, to output.\n"
			<< "Select an option again to toggle it off\n"
			<< "1. Actor/Actress Name\n"
			<< "2. Film Title\n"
			<< "3. Award Name\n"
			<< "4. Year\n"
			<< "5. Won/Lost Award\n"
			<< "6. Print with selected options" << endl;
		cout << "Please choose an option: ";
		cin >> optionOutput;
		if (optionOutput < 1 || optionOutput > 6)
		{
			cout << "Invalid option entered. Please try again.\n" << endl;
		}
	}
	return(optionOutput);
}

int displayProceedConfirmation()
{
	int proceedOption = -1;
	while (proceedOption < 1 || proceedOption > 2)
	{
		cout << "Continue?\n"
			<< "1. Yes\n"
			<< "2. No" << endl;
		cout << "Choose an option: ";
		cin >> proceedOption;
		if (proceedOption < 1 || proceedOption > 2)
		{
			cout << "Invalid option given. Please try again.\n" << endl;
		}
	}
	return(proceedOption);
}

int displayModifyFieldOptions()
{
	int modifyChoice = -1;
	while (modifyChoice < 1 || modifyChoice > 6)
	{
		cout << "Which field(s) do you wish to modify? Please choose one a a time.\n"
			<< "1. Actor/Actress Name\n"
			<< "2. Film Title\n"
			<< "3. Award Name\n"
			<< "4. Year\n"
			<< "5. Won/Lost Award\n"
			<< "6. Return" << endl;
		cout << "Choose an option: ";
		cin >> modifyChoice;
		if (modifyChoice < 1 || modifyChoice > 6)
		{
			cout << "Invalid choice entered. Please try again.\n" << endl;
		}
	}
	return(modifyChoice);
}

int displayActorPrintOptions()
{
	int printOptions = 0;
	while (printOptions < 1 || printOptions > 6)
	{
		cout << "Which field(s) do you wish to print? Please choose one at a time.\n"
			<< "1. Actor/Actress Name\n"
			<< "2. Film Title\n"
			<< "3. Award Name\n"
			<< "4. Year\n"
			<< "5. Won/Lost Award\n"
			<< "6. Print Selected Field(s)" << endl;
		cout << "Choose an option: ";
		cin >> printOptions;
		if (printOptions < 0 || printOptions > 6)
		{
			cout << "Invalid option entered. Please try again.\n" << endl;
		}
	}
	return(printOptions);
}

int displayPicturePrintOptions()
{
	int optionModify = -1;
	while (optionModify < 1 || optionModify > 11)
	{
		cout << "Which field(s) do you wish to print? Please choose one at a time.\n"
			<< "1. Picture Name\n"
			<< "2. Month of Release\n"
			<< "3. Year of Release\n"
			<< "4. Film Duration\n"
			<< "5. Number of Nominations\n"
			<< "6. Genre 1\n"
			<< "7. Genre 2\n"
			<< "8. Film Rating (0-100)\n"
			<< "9. Metacritic Score\n"
			<< "10. Synopsis\n"
			<< "11. Print with selected options" << endl;
		cout << "Please choose an option: ";
		cin >> optionModify;
		if (optionModify < 1 || optionModify > 11)
		{
			cout << "Invalid option entered. Please try again\n" << endl;
		}
	}
	return(optionModify);
}


int displayDataSourceOptions()
{
	int sourceChoice = -1;
	while (sourceChoice < 1 || sourceChoice > 3)
	{
		cout << "\nWhich source do you want to use?\n"
			<< "1. Complete Database\n"
			<< "2. Search Results\n"
			<< "3. Sort Results\n";
		cout << "Choose an option: ";
		cin >> sourceChoice;
		if (sourceChoice < 1 || sourceChoice > 3)
		{
			cout << "Invalid option entered. Please try again.\n" << endl;
		}
	}
	return(sourceChoice);
}

int displayMonthOptions()
{
	int monthChoice = -1;
	while (monthChoice < 1 || monthChoice > 13)
	{
		cout << "Please select a month\n"
			<< "1. January\n"
			<< "2. February\n"
			<< "3. March\n"
			<< "4. April\n"
			<< "5. May\n"
			<< "6. June\n"
			<< "7. July\n"
			<< "8. August\n"
			<< "9. September\n"
			<< "10. October\n"
			<< "11. November\n"
			<< "12. December\n"
			<< "13. Unknown" << endl;
		cout << "Choose a month: ";
		cin >> monthChoice;
		if (monthChoice < 1 || monthChoice > 13)
		{
			cout << "Invalid month entered. Please try again.\n" << endl;
		}
	}
	return(monthChoice);
}

int displayPictureSearchOptions()
{
	int searchOption = -1;
	while (searchOption < 1 || searchOption > 9)
	{
		cout << "Please choose a search option:\n"
			<< "1. Title\n"
			<< "2. Release Month\n"
			<< "3. Release Year\n"
			<< "4. Duration\n"
			<< "5. Genre\n"
			<< "6. Number of Nominations\n"
			<< "7. Film Rating (0-100)\n"
			<< "8. Metacritic Score\n"
			<< "9. Film Synopsis" << endl;
		cout << "Please choose an option: ";
		cin >> searchOption;
		if (searchOption < 1 || searchOption > 9)
		{
			cout << "Invalid option entered. Please try again.\n" << endl;
		}
	}
	return(searchOption);
}

string getStringSearch()
{
	string searchTerm;
	cin.ignore();
	cout << "Please enter a search term: ";
	getline(cin, searchTerm);
	return(searchTerm);
}

//Identical to getStringSearch() but ensures only a number is returned.
string getYearStringSearch()
{
	string searchTerm;
	cin.ignore();
	while (searchTerm.find_first_not_of("0123456789") != searchTerm.npos || searchTerm == "")
	{
		cout << "Please enter a search term: ";
		getline(cin, searchTerm);
		if (searchTerm.find_first_not_of("0123456789") != searchTerm.npos || searchTerm == "")
		{
			cout << "Please enter a number only." << endl;
		}
	}
	if (searchTerm == "")
		searchTerm = "0";
	return(searchTerm);
	
}

//One more for doubles
string getDoubleStringSearch()
{
	string searchTerm;
	cin.ignore();
	while (searchTerm.find_first_not_of("0123456789.") != searchTerm.npos || searchTerm == "")
	{
		cout << "Please enter a search term: ";
		getline(cin, searchTerm);
		if (searchTerm.find_first_not_of("0123456789.") != searchTerm.npos || searchTerm == "")
		{
			cout << "Please enter a number only." << endl;
		}
	}
	if (searchTerm == "")
		searchTerm = "0";
	return(searchTerm);

}

string getFileNameChoice()
{
	string fileChoice;
	cin.ignore(); //may not need
	cout << "Please specify the file to use: ";
	getline(cin, fileChoice);
	return(fileChoice);
}

void fileExistsWarning()
{
	//Warn user of file existing.
	cout << "WARNING: File exists. If you continue, it will be overwritten.\n"
		<< "This action cannot be undone." << endl;
}

//Source for checking if file exists:
//https://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing
bool fileExists(string filename)
{
	ifstream infile(filename);
	return(infile.good());
	//file should close when it leaves scope.
}
