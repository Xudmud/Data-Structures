#include <iostream> //cin, cout, ostream
#include <algorithm> //for sort
#include <vector> //vector
#include <fstream> //fin
#include <sstream> //ss
#include "Vehicle.h"
#include "Recursive.h"



using namespace std;

//Function declarations
int getSearchType();
int searchYear(vector<Vehicle>&);
int searchModel(vector<Vehicle>&);
int searchMake(vector<Vehicle>&);

int main(int argc, char const *argv[])
{
	//Declare variables
	int searchType;
	int resultIndex;

	fstream fin;
	fin.open("vehiclein.txt");
	string line;
	if (fin.fail())
	{
		cout << "Cannot open input file." << endl;
		return(1);
	}
	vector<Vehicle> veh;
	//string x;
	while (!fin.eof())
	{
		//Declare the stream in the while loop, that way ss loses scope
		//when the loop finishes.  ss.clear() wasn't actually clearing the
		//stream, resulting in values piling up.
		stringstream ss;
		getline(fin, line, '|');
		if (!cin)
		{
			cout << "Could not read line." << endl;
		}
		ss << line;
		//push_back() on each entry.
		//push_back a constructor?
		//emplace_back() calls the most appropriate constructor to add the item.
		veh.emplace_back(ss);
		ss.clear();
		getline(fin,line); //Avoid an extra \n at the start of the next stream. Also properly triggers EOF.
	}
	
	searchType = getSearchType();
	switch (searchType)
	{
		case 1:
			resultIndex = searchYear(veh);
			break;
		case 2:
			resultIndex = searchModel(veh);
			break;
		case 3:
			resultIndex = searchMake(veh);
			break;
		default:
			;//This should never exectute.
	}

	//Output result or lack thereof.
	if (resultIndex == -1)
		cout << "Search term not found." << endl;
	else
		cout << "Result: \n" << veh[resultIndex] << endl;

	//Close the input file.
	fin.close();

	return(0);
}

int getSearchType()
{
	int temp;
	cout << "Are you searching by model, make, or year?" << endl;
	cout << "\t1. Year\n\t2. Model\n\t3. Make\n";
	cout << "(Choose one): ";
	do
	{
		cin >> temp;
		if (temp == 1 || temp == 2 || temp == 3)
			return(temp);
		else
			cout << "Please choose from 1 to 3." << endl;
	} while (temp != 1 && temp != 2 && temp != 3);
}

int searchYear(vector<Vehicle>& veh)
{
	//Sort by year
	sort(veh.begin(), veh.end(), Vehicle::yearComp);

	//Get user input
	int yearIn;
	cout << "What year is the vehicle? ";
	cin >> yearIn;
	char choice;

	//Get recursive or iterative
	do
	{
		cout << "Please choose: Recursive or Iterative? (R/I): ";
		cin >> choice;
		switch (choice)
		{
		case 'r':
		case 'R':
			return(Recursive::searchRec(yearIn, veh,0,veh.size() - 1,veh.size()));
			break; //Should never get to this point, but just in case.
		case 'i':
		case 'I':
			return(Recursive::searchIter(yearIn, veh));
			break;
		default:
			cout << "Please choose either R or I." << endl;
			break;
		}
	} while (true); //Switch statement will exit the function on a valid R or I, otherwise we want to try again.
}

int searchModel(vector<Vehicle>& veh)
{
	//Clear the input stream.
	cin.get();

	//Sort by model
	sort(veh.begin(), veh.end(), Vehicle::modelComp);
	string modelIn;
	cout << "What model is the vehicle? ";
	getline(cin,modelIn);

	char choice;
	do
	{
		cout << "Please choose: Recursive or Iterative? (R/I): ";
		cin >> choice;
		switch (choice)
		{
		case 'r':
		case 'R':
			return(Recursive::searchRec(modelIn, veh, 0, veh.size() - 1, veh.size()));
			break; //Should never get to this point, but just in case.
		case 'i':
		case 'I':
			return(Recursive::searchIter(modelIn, veh));
			break;
		default:
			cout << "Please choose either R or I." << endl;
			break;
		}
	} while (true); //Switch statement will exit the function on a valid R or I, otherwise we want to try again.
}

int searchMake(vector<Vehicle>& veh)
{
	//Clear the input stream.
	cin.get();
	
	//Sort by model
	sort(veh.begin(), veh.end(), Vehicle::modelComp);
	string makeIn;
	cout << "What make is the vehicle? ";
	getline(cin,makeIn);

	char choice;
	do
	{
		cout << "Please choose: Recursive or Iterative? (R/I): ";
		cin >> choice;
		switch (choice)
		{
		case 'r':
		case 'R':
			//pass an empty string after model to get the other sort function.
			return(Recursive::searchRec(makeIn, "", veh, 0, veh.size() - 1, veh.size()));
			break; //Should never get to this point, but just in case.
		case 'i':
		case 'I':
			return(Recursive::searchIter(makeIn, "", veh));
			break;
		default:
			cout << "Please choose either R or I." << endl;
			break;
		}
	} while (true); //Switch statement will exit the function on a valid R or I, otherwise we want to try again.
}