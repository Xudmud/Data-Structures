/* Gregory Wicklund
* Class: CSCI-2421
* Final Project ActorFunctions.cpp file
*/

#include "ActorFunctions.h"
#include "MenuFunctions.h"
#include "ActorActress.h"
#include <algorithm>
#include <fstream>


//Verify that the tree actually has data to search.
bool actorSanityCheck(BSTreeActor* act)
{
	//First check for nullptr
	if (act->Root() == nullptr)
		return(false);
	//Next check for default key.
	else if (act->Root()->Key() == "-1")
		return(false);
	else
		return(true);
}

//Add 
Actor getNewActorData()
{
	string str;
	Actor temp;
	cout << "Adding a new Actor/Actress object" << endl;
	cout << "Name? ";
	getline(cin, str);
	temp.name = str;
	cout << "Film? ";
	getline(cin, str);
	temp.film = str;
	cout << "Year? ";
	
	
	while (str.find_first_not_of("0123456789") != str.npos)
	{
		getline(cin, str);
		if (str.find_first_not_of("0123456789") != str.npos)
		{
			cout << "Please enter a number only, or leave blank." << endl;
		}
	}
	if (str == "")
	{
		temp.year = 0;
	}
	else
	{
		temp.year = stoi(str);
	}
	cout << "Award Name? ";
	getline(cin, str);
	temp.award = str;
	switch (displayActorWinLoseOptions())
	{
	case 1:
		temp.winner = true;
		break;
	case 2:
		temp.winner = false;
		break;
	default:
		//Assume not a winner
		cout << "Invalid option given. Assuming did not win.\n" << endl;
		temp.winner = false;
	}

	return(temp);
}

vector<Actor> searchActor(BSTreeActor* act)
{
	vector<Actor> temp;
	if (!actorSanityCheck(act))
	{
		cout << "No data in Actors to search.\n" << endl;
		return(emptyActorData());
	}
	//implied else
	switch (displayActorSearchOptions())
	{
	case 1:
		temp = searchActorName(act);
		break;
	case 2:
		temp = searchFilmTitle(act);
		break;
	case 3:
		temp = searchAward(act);
		break;
	case 4:
		temp = searchYear(act);
		break;
	case 5:
		temp = searchWinLose(act);
		break;
	default:
		//This code should never run, but just in case.
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(temp);
	}
	//At this point, we should have a vector with search results.
	//Check if the vector is empty or has one result.
	if (temp.size() == 0)
	{
		cout << "No results found. Returning to main menu.\n" << endl;
		return(temp);
	}
	//Switch statement will handle returning the vector.
	while (temp.size() != 0)
	{
		cout << "Found " << temp.size() << " result(s).\n";
		switch (displaySearchWithinResultsOptions())
		{
		case 1:
			temp = searchActorResults(temp);
			break;
		case 2:
			return(temp);
			break;
		default:
			cout << "Invalid option given. Returning to main menu.\n" << endl;
			return(temp);
		}
		if (temp.size() == 0)
		{
			cout << "No results found. Returning to main menu.\n" << endl;
		}
	}
	return(temp);
}

vector<Actor> searchActorName(BSTreeActor* act)
{
	//Possibly redundant, but ensure that we don't hit a nullptr
	if (!actorSanityCheck(act))
	{
		cout << "No data in Actors to search.\n" << endl;
		return(emptyActorData());
	}
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		//Using searchTerm as the key, search the tree.
		return(act->searchFullActorName(act->Root(), searchTerm));
		break;
	case 2:
		return(act->searchPartialActorName(act->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu\n" << endl;
		return(emptyActorData());
	}
}

vector<Actor> searchFilmTitle(BSTreeActor* act)
{
	if (!actorSanityCheck(act))
	{
		cout << "No data in Actors to search.\n" << endl;
		return(emptyActorData());
	}
	//implied else
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(act->searchFullFilm(act->Root(), searchTerm));
		break;
	case 2:
		return(act->searchPartialFilm(act->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered.\n" << endl;
		return(emptyActorData());
	}
}

vector<Actor> searchYear(BSTreeActor* act)
{
	if (!actorSanityCheck(act))
	{
		cout << "No data in Actors to search.\n" << endl;
		return(emptyActorData());
	}
	//implied else
	//Get the search term as string; use stoi for a complete search, cast the year as string for partial.
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(act->searchFullYear(act->Root(), stoi(searchTerm)));
		break;
	case 2:
		return(act->searchPartialYear(act->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered.\n" << endl;
		return(emptyActorData());
	}
}

vector<Actor> searchAward(BSTreeActor* act)
{
	if (!actorSanityCheck(act))
	{
		cout << "No data in Actors to search.\n" << endl;
		return(emptyActorData());
	}
	//implied else
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(act->searchFullAward(act->Root(), searchTerm));
		break;
	case 2:
		return(act->searchPartialAward(act->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered.\n" << endl;
		return(emptyActorData());
	}
}

vector<Actor> searchWinLose(BSTreeActor* act)
{
	if (!actorSanityCheck(act))
	{
		cout << "No data in Actors to search.\n" << endl;
		return(emptyActorData());
	}
	switch (displayActorWinLoseOptions())
	{
	case 1:
		return(act->searchWinLose(act->Root(), true));
		break;
	case 2:
		return(act->searchWinLose(act->Root(), false));
		break;
	default:
		cout << "Invalid option entered.\n" << endl;
		return(emptyActorData());
	}
}

//Read in from file. Current limitation: Will add entries even if they
//already exist in the tree.
void readActorsIn(string fileChoice, BSTreeActor* treeAct)
{
	//Read in the file to the actor binary search tree
	ifstream finact;
	string temp; //container for the first line
	finact.open(fileChoice);
	if (finact.fail())
	{
		cout << "Error opening input file. Please try again.\n" << endl;
		return;
	}
	//Discard the first line of the input file.
	getline(finact, temp);
	if (temp != "Year,Award,Winner,Name,Film" && temp != "Year,Award,Winner,Name,Film,")
	{
		cout << "Error: Unable to read file (wrong form of data)\n" << endl;
		finact.close();
		return;
	}
	while (!finact.eof())
	{
		Actor act = treeAct->readInput(finact);
		//Check if the entry is blank (seems to happen on eof)
		if(!defaultActor(act))
		{
			treeAct->addNode(act.name, act);
		}
	}
	//Done with the input file, so now we can close it.
	finact.close();
	cout << "Successfully read in actors." << endl;
	//Function to print current count
	treeAct->printActorCount();
}

vector<Actor> searchActorResults(vector<Actor> vec)
{
	if (vec.size() == 0)
	{
		cout << "No results to search from.\n" << endl;
		return(vec);
	}
	//implied else
	switch (displayActorSearchOptions())
	{
	case 1:
		return(searchActorResultsName(vec));
		break;
	case 2:
		return(searchActorResultsFilm(vec));
		break;
	case 3:
		return(searchActorResultsAward(vec));
		break;
	case 4:
		return(searchActorResultsYear(vec));
		break;
	case 5:
		return(searchActorResultsWinLose(vec));
		break;
	default:
		cout << "Invalid option entered.\n" << endl;
		return(vec);
	}
}

//Search within results functions. Since these are working with the returned vector,
//I use them here instead of member functions of the BSTree or Node classes.
vector<Actor> searchActorResultsName(vector<Actor> vec)
{
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchActorResultsFullName(vec, searchTerm));
		break;
	case 2:
		return(searchActorResultsPartialName(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec); //Return the vector unchanged.
	}
}

vector<Actor> searchActorResultsFullName(vector<Actor> vec, string searchTerm)
{
	//Create a temp vector
	vector<Actor> temp;
	//Iterate through the vector, adding results to a new vector to be returned.
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].name == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsPartialName(vector<Actor> vec, string searchTerm)
{
	vector<Actor> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].name.find(searchTerm) != vec[i].name.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsFilm(vector<Actor> vec)
{
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchActorResultsFullFilm(vec, searchTerm));
		break;
	case 2:
		return(searchActorResultsPartialFilm(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given\n" << endl;
		return(vec); //Return the vector unchanged.
	}
}

vector<Actor> searchActorResultsFullFilm(vector<Actor> vec, string searchTerm)
{
	//Create a temp vector
	vector<Actor> temp;
	//Iterate through the vector, adding results to a new vector to be returned.
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].film == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsPartialFilm(vector<Actor> vec, string searchTerm)
{
	vector<Actor> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].film.find(searchTerm) != vec[i].film.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsAward(vector<Actor> vec)
{
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchActorResultsFullAward(vec, searchTerm));
		break;
	case 2:
		return(searchActorResultsPartialAward(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given\n" << endl;
		return(vec); //Return the vector unchanged.
	}
}

vector<Actor> searchActorResultsFullAward(vector<Actor> vec, string searchTerm)
{
	//Create a temp vector
	vector<Actor> temp;
	//Iterate through the vector, adding results to a new vector to be returned.
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].award == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsPartialAward(vector<Actor> vec, string searchTerm)
{
	vector<Actor> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].award.find(searchTerm) != vec[i].award.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsYear(vector<Actor> vec)
{
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchActorResultsFullYear(vec, stoi(searchTerm)));
		break;
	case 2:
		return(searchActorResultsPartialYear(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given\n" << endl;
		return(vec); //Return the vector unchanged.
	}
}

vector<Actor> searchActorResultsFullYear(vector<Actor> vec, int searchTerm)
{
	//Create a temp vector
	vector<Actor> temp;
	//Iterate through the vector, adding results to a new vector to be returned.
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].year == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsPartialYear(vector<Actor> vec, string searchTerm)
{
	vector<Actor> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (to_string(vec[i].year).find(searchTerm) != to_string(vec[i].year).npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsWinLose(vector<Actor> vec)
{
	switch (displayActorWinLoseOptions())
	{
	case 1:
		return(searchActorResultsWin(vec));
		break;
	case 2:
		return(searchActorResultsLose(vec));
		break;
	default:
		cout << "Invalid option given\n" << endl;
		return(vec);
	}
}

vector<Actor> searchActorResultsWin(vector<Actor> vec)
{
	vector<Actor> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].winner)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Actor> searchActorResultsLose(vector<Actor> vec)
{
	vector<Actor> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (!vec[i].winner)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

//Modify data. Search down to one result, then prompt which field (if any) to modify.
//Receive: Actor tree
//Return type: void
void modifyActorData(BSTreeActor* act)
{
	if (!actorSanityCheck(act))
	{
		cout << "No data in Actors to modify. Returning to main menu.\n" << endl;
		return;
	}
	//Call search function to get a single Actor object.
	vector<Actor> temp = searchActor(act);
	while (temp.size() > 1)
	{
		cout << "Too many results." << endl;
		switch (displayProceedConfirmation())
		{
		case 1:
			temp = searchActorResults(temp);
			break;
		case 2:
			//User does not want to continue, return without doing anything.
			return;
			break;
		default:
			cout << "Invalid option given. Returning to main menu.\n" << endl;
			return;
		}
	}
	//At this point, temp's size should be 0 or 1.
	if (temp.size() == 0)
	{
		cout << "No elements to modify. Returning to menu.\n" << endl;
	}
	else
	{
		modifyActorNode(act, temp[0]);
	}
}

vector<Actor> emptyActorData()
{
	//Called if an empty Actor vector is needed. Creates said empty vector and returns it.
	vector<Actor> temp;
	return(temp);
}

//Add Function
void addActorNode(BSTreeActor* act)
{
	//Flush the input stream
	cin.ignore();
	//No need to check if the tree is empty; this function permits adding to an "empty" tree.
	Actor temp = getNewActorData();
	act->addNode(temp.name, temp);
}

//Delete functions.
void deleteActorNode(BSTreeActor* act)
{
	if (!actorSanityCheck(act))
	{
		cout << "No data in Actors to remove. Returning to main menu.\n" << endl;
		return;
	}
	vector<Actor> temp;
	cout << "First, search for Actor(s) to remove." << endl;
	temp = searchActor(act);
	if (temp.size() == 0)
		return; //Nothing to remove, no need to stay here.
	cout << "Removing " << temp.size() << " elements from Actors.\n"
		<< "Elements to remove: " << endl;
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		printActor(temp[i]);
		cout << endl;
	}
	//Function to output vector. Can potentially use same function for outputting the list to stdout.
	switch (displayProceedConfirmation())
	{
	case 1:
		deleteSelectedNodes(act, temp);
		break;
	case 2:
		return;
		break;
	default:
		cout << "Invalid input given. Returning to main menu.\n" << endl;
		return;
	}
}

//Modify function (specifically gathering modified data)
Actor changeActorFields(Actor act)
{
	string str;
	while (true)
	{
		//Get user's choice, and modify fields accordingly. Go until they're done, then return
		//the new object.
		switch (displayModifyFieldOptions())
		{
		case 1:
			cout << "Enter new name: ";
			getline(cin, str);
			act.name = str;
			break;
		case 2:
			cout << "Enter new title: ";
			getline(cin, str);
			act.film = str;
			break;
		case 3:
			cout << "Enter new award name: ";
			getline(cin, str);
			act.film = str;
			break;
		case 4:
			str = "";
			while (str.find_first_not_of("0123456789") != str.npos)
			{
				cout << "Enter year for film. If unknown, please use 0: ";
				getline(cin, str);
				if (str.find_first_not_of("0123456789") != str.npos)
				{
					cout << "Please enter a number for year.\n" << endl;
				}
			}
			act.year = stoi(str);
			break;
		case 5:
			switch (displayActorWinLoseOptions())
			{
			case 1:
				act.winner = true;
				break;
			case 2:
				act.winner = false;
				break;
			default:
				cout << "Invalid input given. Assuming not a winner.\n" << endl;
				act.winner = false;
				break;
			}
			case 6:
				//Called when user is ready to go back.
				return(act);
				break;
			default:
				cout << "Invalid input given.\n" << endl;
		}
	}
	//Return the actor object here, just in case somehow the while loop gets broken out of.
	return(act);
}

void deleteSelectedNodes(BSTreeActor* act, const vector<Actor>& vec)
{
	//For each element in vec, find the associated node, and remove it.
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		NodeActor* temp = new NodeActor;
		temp = act->findNode(vec[i].name);
		if (temp != nullptr)
		{
			//Limitation: Delete might not cover all instances, based on the order nodes get deleted.
			//Can mitigate by calling/creating a deleteNode with additional parameters.
			if (temp->Data() == vec[i])
			{
				act->deleteNode(temp->Key());
			}
		}
	}
}

bool defaultActor(Actor act)
{
	//Build an empty Actor object
	Actor temp;
	//Use the overloaded == operator to check if act matches default
	return(act == temp);
}

//Modify function
//Receive in the Actor object. Create a new actor object, change appropriate data.
//Call a modifyActorNode() recursive to get the correct node, then set the new data and key.
//Limitation: If name is changed, delete node and re-add it to preserve BSTree sorting.
void modifyActorNode(BSTreeActor* tree, Actor act)
{
	Actor temp = changeActorFields(act);

	NodeActor* node = tree->findNode(act.name);
	if (node == nullptr)
	{
		cout << "Could not find node. Returning.\n" << endl;
		return;
	}
	//Current limitation: Can't delete if a duplicate name exists, based on current find/delete functions.
	//Could possibly delete the bad node and re-add it, which would put it farther down the tree.
	//This could allow access to the correct node to modify.
	if (!(node->Data() == act))
	{
		cout << "Unable to modify Actor data.\n" << endl;
		return;
	}
	else
	{
		//Delete the old node, add the new node.
		tree->deleteNode(act.name);
		tree->addNode(temp.name, temp);
	}
}

//Sort function (complete)
vector<Actor> sortActors(BSTreeActor* treeAct)
{
	if (!actorSanityCheck(treeAct))
	{
		cout << "No data in Actors to sort. Returning to main menu.\n" << endl;
		return(emptyActorData());
	}
	vector<Actor> temp;
	//Determine which field to sort from
	switch (displayActorSortOptions())
	{
	case 1:
		return(treeAct->sortByName(treeAct->Root()));
		break;
	case 2:
		return(treeAct->sortByFilm(treeAct->Root()));
		break;
	case 3:
		return(treeAct->sortByAward(treeAct->Root()));
		break;
	case 4:
		return(treeAct->sortByYear(treeAct->Root()));
		break;
	case 5:
		return(treeAct->sortByWinner(treeAct->Root()));
		break;
	default:
		cout << "Invalid option entered. Returning unsorted.\n" << endl;
		treeAct->buildVector(treeAct->Root(), temp);
		return(temp);
	}
}

//Sort function (results)
vector<Actor> sortActors(const vector<Actor>& vec)
{
	switch (displayActorSortOptions())
	{
	case 1:
		return(sortByName(vec));
		break;
	case 2:
		return(sortByFilm(vec));
		break;
	case 3:
		return(sortByYear(vec));
		break;
	case 4:
		return(sortByAward(vec));
		break;
	case 5:
		return(sortByWinner(vec));
		break;
	default:
		cout << "Invalid input entered. Returning unsorted.\n" << endl;
		return(vec);
	}
}

//Functions for sorting search results
vector<Actor> sortByName(vector<Actor> vec)
{
	sort(vec.begin(), vec.end(), compareName);
	return(vec);
}

vector<Actor> sortByFilm(vector<Actor> vec)
{
	sort(vec.begin(), vec.end(), compareFilm);
	return(vec);
}

vector<Actor> sortByYear(vector<Actor> vec)
{
	sort(vec.begin(), vec.end(), compareYear);
	return(vec);
}

vector<Actor> sortByAward(vector<Actor> vec)
{
	sort(vec.begin(), vec.end(), compareAward);
	return(vec);
}

vector<Actor> sortByWinner(vector<Actor> vec)
{
	sort(vec.begin(), vec.end(), compareWinner);
	return(vec);
}


//Print functions
//Print the database out in csv form
void printActorsToFile(BSTreeActor* tree)
{
	cout << "Printing full database to file.\n";
	string str;
	ofstream fout;
	bool done = false;
	str = getFileNameChoice();
	if (fileExists(str))
	{
		fileExistsWarning();
		switch (displayProceedConfirmation())
		{
		case 1:
			//Open the output file and verify it opened.
			fout.open(str);
			if (fout.fail())
				//File did not open, prompt again for filename.
			{
				cout << "Error opening output file. Please try again.\n" << endl;
			}
			else
				//File opened, set done to true.
			{
				done = true;
			}
			break;
		case 2:
			cout << "Operation cancelled." << endl;
			switch (displayProceedConfirmation())
			{
			case 1:
				//Do nothing
				break;
			case 2:
				return;
				break;
			default:
				return;
				break;
			}
			break;
		default:
			cout << "Invalid input given. Assuming no overwrite.\n" << endl;
		}
	}
	else
		//File does not exist, attempt to open it.
	{
		fout.open(str);
		if (fout.fail())
		{
			cout << "Error opening output file. Please try again.\n" << endl;
		}
		else
		{
			done = true;
		}
	}
	printActorHead(fout);
	tree->printFileInOrder(fout);
	fout.close();
	cout << "Done. Please check " + str + " for the output.\n" << endl;
}

void printActorHead(ostream& out)
{
	out << "Year,Award,Winner,Name,Film" << endl;
}

//Main print function. Receives a vector of Actor objects, prints them to file.
void printActorsToFile(vector<Actor> vec)
{
	//Create an array of booleans to determine what to print.
	cin.ignore();
	bool fieldsToPrint[5] = { false,false,false,false,false };
	bool done = false;
	string str;
	ofstream fout;
	//Get fields to print.
	while (!done)
	{
		displayCurrentChoices(fieldsToPrint);
		switch (displayActorPrintOptions())
		{
		case 1:
			fieldsToPrint[0] = !fieldsToPrint[0];
			break;
		case 2:
			fieldsToPrint[1] = !fieldsToPrint[1];
			break;
		case 3:
			fieldsToPrint[2] = !fieldsToPrint[2];
			break;
		case 4:
			fieldsToPrint[3] = !fieldsToPrint[3];
			break;
		case 5:
			fieldsToPrint[4] = !fieldsToPrint[4];
			break;
		case 6:
			done = true;
			break;
		default:
			cout << "Invalid input given. Aborting.\n" << endl;
			return;
		} //switch
	} //while

	//Get output file name
	//Switch done back to false.
	done = false;
	while (!done)
	{
		str = getFileNameChoice();
		//Check if the file exists.
		if (fileExists(str))
		{
			fileExistsWarning();
			switch (displayProceedConfirmation())
			{
			case 1:
				//Open the output file and verify it opened.
				fout.open(str);
				if (fout.fail())
					//File did not open, prompt again for filename.
				{
					cout << "Error opening output file. Please try again.\n" << endl;
				}
				else
					//File opened, set done to true.
				{
					done = true;
				}
				break;
			case 2:
				cout << "Operation cancelled." << endl;
				switch (displayProceedConfirmation())
				{
				case 1:
					//Do nothing
					break;
				case 2:
					return;
					break;
				default:
					return;
					break;
				}
				break;
			default:
				cout << "Invalid input given. Assuming no overwrite.\n" << endl;
			}
		}
		else
			//File does not exist, attempt to open it.
		{
			fout.open(str);
			if (fout.fail())
			{
				cout << "Error opening output file. Please try again.\n" << endl;
			}
			else
			{
				done = true;
			}
		}
	}

	printActor(fout, fieldsToPrint);
	//At this point, the file is opened, so print the resulting fields to it.
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		printActor(fout, vec[i], fieldsToPrint);
	}
	//We're done with the output file, so now we can close it.
	fout.close();
	cout << "Done. Please check " + str + " for the output.\n" << endl;
}

//Functions for fout to print
//Header for file
void printActor(ofstream& fout, const bool fieldsToPrint[5])
{
	//Using fout spacing to get specific lengths.
	//There may be a small amount of overflow on very long fields.
	fout << '|';
	//Actor length: 20 characters
	if (fieldsToPrint[0])
	{
		fout << "Actor/Actress Name";
		for (unsigned int i = 0; i < 2; i++)
		{
			fout << " ";
		}
		fout << '|';
	}
	//Film length: 30 characters
	if (fieldsToPrint[1])
	{
		fout << "Film Title";
		for (unsigned int i = 0; i < 20; i++)
		{
			fout << " ";
		}
		fout << '|';
	}
	//Year is a constant four characters.
	if (fieldsToPrint[3])
	{
		fout << "Year";
		fout << '|';
	}
	//Award length: 35 characters
	if (fieldsToPrint[2])
	{
		fout << "Award Name";
		for (unsigned int i = 0; i < 25; i++)
		{
			fout << " ";
		}
		fout << '|';
	}
	//Boolean winner is a single character, field is 6 for length of header.
	if (fieldsToPrint[4])
	{
		fout << "Winner";
		fout << '|';
	}
	fout << "\n";
}

void printActor(ofstream& fout, Actor act, const bool fieldsToPrint[5])
{
	//Step through each boolean for fieldsToPrint, print its corresponding value if needed.
	fout << '|';
	//Actor length: 20 characters
	if (fieldsToPrint[0])
	{
		fout << act.name;
		//Guard against underflow
		if (act.name.size() < 20)
		{
			for (unsigned int i = 0; i < 20 - act.name.size(); i++)
			{
				//fill() should default to space, but specifying just in case.
				fout << " ";
			}
		}
		fout << '|';
	}
	//Film length: 30 characters
	if (fieldsToPrint[1])
	{
		fout << act.film;
		if (act.film.size() < 30)
		{
			for (unsigned int i = 0; i < 30 - act.film.size(); i++)
			{
				fout << " ";
			}
		}
		fout << '|';
	}
	//Year is a constant four characters.
	if (fieldsToPrint[3])
	{
		fout << act.year;
		fout << '|';
	}
	//Award length: 35 characters
	if (fieldsToPrint[2])
	{
		fout << act.award;
		if (act.award.size() < 35)
		{
			for (unsigned int i = 0; i < 35 - act.award.size(); i++)
			{
				fout << " ";
			}
		}
	}
	fout << '|';
	//Boolean winner is a single character, field is 6 for length of header.
	if (fieldsToPrint[4])
	{
		if (act.winner)
			fout << "Yes   ";
		else
			fout << "No    ";
		fout << '|';
	}
	fout << "\n";
}


void printActor(const Actor& act)
{
	cout << act.year << ',' << act.award << ',';
	if (act.winner)
		cout << "1";
	else
		cout << "0";
	cout << ',' << act.name << ',' << act.film << endl;
}

void displayCurrentChoices(const bool fieldsToPrint[5])
{
	cout << "Current fields to print:\n";
	//Series of if-statements, I'm not seeing an easier way to do this at the moment.
	if (fieldsToPrint[0])
	{
		cout << "Actor/Actress Name\n";
	}
	if (fieldsToPrint[1])
	{
		cout << "Film Title\n";
	}
	if (fieldsToPrint[2])
	{
		cout << "Award Name\n";
	}
	if (fieldsToPrint[3])
	{
		cout << "Year\n";
	}
	if (fieldsToPrint[4])
	{
		cout << "Won/Lost Award\n";
	}
	cout << endl;
}
