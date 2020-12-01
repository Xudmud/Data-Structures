#include "PictureFunctions.h"
#include "MenuFunctions.h"
#include <algorithm>
#include <vector>
#include <fstream>

//Verify the picture tree has data to search
bool pictureSanityCheck(BSTreePicture* pict)
{
	if (pict->Root() == nullptr)
		return(false);
	else if (pict->Root()->Key() == "-1")
		return(false);
	else
		return(true);
}

//Add new picture
Picture getNewPictureData()
{
	string str;
	Picture temp;
	cout << "Adding a new Picture object" << endl;
	//Get movie title
	cout << "Movie Title? ";
	getline(cin, str);
	temp.name = str;
	//Get release month
	cout << "Release month?" << endl;
	switch (displayMonthOptions())
	{
	case 1:
		temp.release = "January";
		break;
	case 2:
		temp.release = "February";
		break;
	case 3:
		temp.release = "March";
		break;
	case 4:
		temp.release = "April";
		break;
	case 5:
		temp.release = "May";
		break;
	case 6:
		temp.release = "June";
		break;
	case 7:
		temp.release = "July";
		break;
	case 8:
		temp.release = "August";
		break;
	case 9:
		temp.release = "September";
		break;
	case 10:
		temp.release = "October";
		break;
	case 11:
		temp.release = "November";
		break;
	case 12:
		temp.release = "December";
		break;
	default:
		temp.release = "";
	}
	cin.ignore();
	//Get release year
	cout << "Release year? ";
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
	//intentionally set string so the while loop goes.
	//Alternative: do-while instead of while
	str = "-1";
	//Get duration
	cout << "Duration? ";
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
		temp.duration = 0;
	}
	else
	{
		temp.duration = stoi(str);
	}

	//Get genre1
	cout << "First genre? ";
	getline(cin, str);
	temp.genre1 = str;

	//Get genre2
	cout << "Second genre? ";
	getline(cin, str);
	temp.genre2 = str;
	//Get number of nominations
	cout << "Number of nominations? ";
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
		temp.nominations = 0;
	}
	else
	{
		temp.nominations = stoi(str);
	}
	
	str = "-1";
	//Get rating
	cout << "Film rating? (0-100): ";
	while (str.find_first_not_of("0123456789.") != str.npos)
	{
		getline(cin, str);
		if (str.find_first_not_of("0123456789.") != str.npos)
		{
			cout << "Please enter a number only, or leave blank." << endl;
		}
	}
	if (str == "" || str == ".") //avoid setting an absurdly-small-but-not-quite-zero value
	{
		temp.rating = 0;
	}
	else
	{
		//since stoi is string-to-int, it stands to reason that stod is string-to-double
		temp.rating = stod(str);
	}

	str = "-1";
	//Get metacritic score
	cout << "Metacritic score? ";
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
		temp.metacritic = 0;
	}
	else
	{
		temp.metacritic = stoi(str);
	}
	//Get synopsis
	cout << "Film synopsis? ";
	getline(cin, str);
	temp.synopsis = str;
	
	//Return the newly-built Picture object
	return(temp);
}

vector<Picture> searchPicture(BSTreePicture* pict)
{
	vector<Picture> temp;
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	switch (displayPictureSearchOptions())
	{
	case 1:
		temp = searchPictureName(pict);
		break;
	case 2:
		temp = searchPictureRelease(pict);
		break;
	case 3:
		temp = searchPictureYear(pict);
		break;
	case 4:
		temp = searchPictureDuration(pict);
		break;
	case 5:
		//Genre search will search both genre fields
		temp = searchPictureGenre(pict);
		break;
	case 6:
		temp = searchPictureNominations(pict);
		break;
	case 7:
		temp = searchPictureRating(pict);
		break;
	case 8:
		temp = searchPictureMetacritic(pict);
		break;
	case 9:
		temp = searchPictureSynopsis(pict);
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(temp);
	}

	if (temp.size() == 0)
	{
		cout << "No results found. Returning to main menu\n" << endl;
		return(temp);
	}

	while (temp.size() != 0)
	{
		cout << "Found " << temp.size() << "result(s).\n";
		switch (displaySearchWithinResultsOptions())
		{
		case 1:
			temp = searchPictureResults(temp);
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

vector<Picture> searchPictureName(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(pict->searchFullPictureName(pict->Root(), searchTerm));
		break;
	case 2:
		return(pict->searchPartialPictureName(pict->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
}

vector<Picture> searchPictureRelease(BSTreePicture* pict)
{
	switch (displayMonthOptions())
	{
	case 1:
		return(pict->searchPictureRelease(pict->Root(), "January"));
		break;
	case 2:
		return(pict->searchPictureRelease(pict->Root(), "February"));
		break;
	case 3:
		return(pict->searchPictureRelease(pict->Root(), "March"));
		break;
	case 4:
		return(pict->searchPictureRelease(pict->Root(), "April"));
		break;
	case 5:
		return(pict->searchPictureRelease(pict->Root(), "May"));
		break;
	case 6:
		return(pict->searchPictureRelease(pict->Root(), "June"));
		break;
	case 7:
		return(pict->searchPictureRelease(pict->Root(), "July"));
		break;
	case 8:
		return(pict->searchPictureRelease(pict->Root(), "August"));
		break;
	case 9:
		return(pict->searchPictureRelease(pict->Root(), "September"));
		break;
	case 10:
		return(pict->searchPictureRelease(pict->Root(), "October"));
		break;
	case 11:
		return(pict->searchPictureRelease(pict->Root(), "November"));
		break;
	case 12:
		return(pict->searchPictureRelease(pict->Root(), "December"));
		break;
	case 13:
		return(pict->searchPictureRelease(pict->Root(), ""));
		break;
	default:
		cout << "Unexpected error. No results available.\n" << endl;
		return(emptyPictureData());
	}
}

vector<Picture> searchPictureYear(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(pict->searchFullPictureYear(pict->Root(), stoi(searchTerm)));
		break;
	case 2:
		return(pict->searchPartialPictureYear(pict->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
}

vector<Picture> searchPictureDuration(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(pict->searchFullPictureDuration(pict->Root(), stoi(searchTerm)));
		break;
	case 2:
		return(pict->searchPartialPictureDuration(pict->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
}

vector<Picture> searchPictureGenre(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(pict->searchFullPictureGenre(pict->Root(), searchTerm));
		break;
	case 2:
		return(pict->searchPartialPictureGenre(pict->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
}

vector<Picture> searchPictureNominations(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(pict->searchFullPictureNominations(pict->Root(), stoi(searchTerm)));
		break;
	case 2:
		return(pict->searchPartialPictureNominations(pict->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
}

vector<Picture> searchPictureRating(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	string searchTerm = getDoubleStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(pict->searchFullPictureRating(pict->Root(), stod(searchTerm)));
		break;
	case 2:
		return(pict->searchPartialPictureRating(pict->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
}

vector<Picture> searchPictureMetacritic(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(pict->searchFullPictureMetacritic(pict->Root(), stoi(searchTerm)));
		break;
	case 2:
		return(pict->searchPartialPictureMetacritic(pict->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
}

vector<Picture> searchPictureSynopsis(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to search.\n" << endl;
		return(emptyPictureData());
	}
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(pict->searchFullPictureSynopsis(pict->Root(), searchTerm));
		break;
	case 2:
		return(pict->searchPartialPictureSynopsis(pict->Root(), searchTerm));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
}

void readPicturesIn(string fileChoice, BSTreePicture* treePict)
{
	ifstream finpict;
	string temp;
	finpict.open(fileChoice);
	if (finpict.fail())
	{
		cout << "Error opening input file. Please try again.\n" << endl;
		return;
	}

	getline(finpict, temp);
	//Check to make sure the key matches up
	if (temp != "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis")
	{
		cout << "Error: Unable to read file (wrong form of data).\n" << endl;
		//close the input stream
		finpict.close();
		return;
	}
	while (!finpict.eof())
	{
		Picture pict = treePict->readInput(finpict);
		//Check if the entry is blank
		if (!defaultPicture(pict))
		{
			treePict->addNode(pict.name, pict);
		}
	}
	finpict.close();
	cout << "Successfully read in pictures." << endl;
	treePict->printPictureCount();
}

//Search result functions
vector<Picture> searchPictureResults(vector<Picture> vec)
{
	if (vec.size() == 0)
	{
		cout << "No results to search from. Returning to main menu.\n" << endl;
		return(vec);
	}

	switch (displayPictureSearchOptions())
	{
	case 1:
		return(searchPictureResultsName(vec));
		break;
	case 2:
		return(searchPictureResultsRelease(vec));
		break;
	case 3:
		return(searchPictureResultsYear(vec));
		break;
	case 4:
		return(searchPictureResultsDuration(vec));
		break;
	case 5:
		//Genre search will search both genre fields
		return(searchPictureResultsGenre(vec));
		break;
	case 6:
		return(searchPictureResultsNominations(vec));
		break;
	case 7:
		return(searchPictureResultsRating(vec));
		break;
	case 8:
		return(searchPictureResultsMetacritic(vec));
		break;
	case 9:
		return(searchPictureResultsSynopsis(vec));
		break;
	default:
		cout << "Invalid option entered. Returning to main menu.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsName(vector<Picture> vec)
{
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchPictureResultsFullName(vec, searchTerm));
		break;
	case 2:
		return(searchPictureResultsPartialName(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsFullName(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].name == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsPartialName(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].name.find(searchTerm) != vec[i].name.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsRelease(vector<Picture> vec)
{
	//Switch to pass the release month to the function
	switch (displayMonthOptions())
	{
	case 1:
		return(searchPictureResultsRelease(vec, "January"));
		break;
	case 2:
		return(searchPictureResultsRelease(vec, "February"));
		break;
	case 3:
		return(searchPictureResultsRelease(vec, "March"));
		break;
	case 4:
		return(searchPictureResultsRelease(vec, "April"));
		break;
	case 5:
		return(searchPictureResultsRelease(vec, "May"));
		break;
	case 6:
		return(searchPictureResultsRelease(vec, "June"));
		break;
	case 7:
		return(searchPictureResultsRelease(vec, "July"));
		break;
	case 8:
		return(searchPictureResultsRelease(vec, "August"));
		break;
	case 9:
		return(searchPictureResultsRelease(vec, "September"));
		break;
	case 10:
		return(searchPictureResultsRelease(vec, "October"));
		break;
	case 11:
		return(searchPictureResultsRelease(vec, "November"));
		break;
	case 12:
		return(searchPictureResultsRelease(vec, "December"));
		break;
	case 13:
		return(searchPictureResultsRelease(vec, ""));
		break;
	default:
		cout << "Unknown error occurred. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsRelease(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].name == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsYear(vector<Picture> vec)
{
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchPictureResultsFullYear(vec, stoi(searchTerm)));
		break;
	case 2:
		return(searchPictureResultsPartialYear(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsFullYear(vector<Picture> vec, int searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].year == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsPartialYear(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (to_string(vec[i].year).find(searchTerm) != vec[i].name.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsDuration(vector<Picture> vec)
{
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchPictureResultsFullYear(vec, stoi(searchTerm)));
		break;
	case 2:
		return(searchPictureResultsPartialName(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsFullDuration(vector<Picture> vec, int searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].duration == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsPartialDuration(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (to_string(vec[i].duration).find(searchTerm) != vec[i].name.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

//Genre search searches both genres
vector<Picture> searchPictureResultsGenre(vector<Picture> vec)
{
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchPictureResultsFullName(vec, searchTerm));
		break;
	case 2:
		return(searchPictureResultsPartialName(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsFullGenre(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].genre1 == searchTerm || vec[i].genre2 == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsPartialGenre(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if ((vec[i].genre1.find(searchTerm) != vec[i].name.npos) || (vec[i].genre2.find(searchTerm) != vec[i].name.npos))
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsNominations(vector<Picture> vec)
{
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchPictureResultsFullNominations(vec, stoi(searchTerm)));
		break;
	case 2:
		return(searchPictureResultsPartialNominations(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsFullNominations(vector<Picture> vec, int searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].nominations == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsPartialNominations(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (to_string(vec[i].nominations).find(searchTerm) != vec[i].name.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsRating(vector<Picture> vec)
{
	string searchTerm = getDoubleStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchPictureResultsFullRating(vec, stod(searchTerm)));
		break;
	case 2:
		return(searchPictureResultsPartialRating(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsFullRating(vector<Picture> vec, double searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].rating == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsPartialRating(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (to_string(vec[i].rating).find(searchTerm) != vec[i].name.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsMetacritic(vector<Picture> vec)
{
	string searchTerm = getYearStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchPictureResultsFullMetacritic(vec, stoi(searchTerm)));
		break;
	case 2:
		return(searchPictureResultsPartialName(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsFullMetacritic(vector<Picture> vec, int searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].metacritic == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsPartialMetacritic(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (to_string(vec[i].metacritic).find(searchTerm) != vec[i].name.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsSynopsis(vector<Picture> vec)
{
	string searchTerm = getStringSearch();
	switch (displayPartialCompleteOptions())
	{
	case 1:
		return(searchPictureResultsFullSynopsis(vec, searchTerm));
		break;
	case 2:
		return(searchPictureResultsPartialSynopsis(vec, searchTerm));
		break;
	default:
		cout << "Invalid option given. Returning vector unchanged.\n" << endl;
		return(vec);
	}
}

vector<Picture> searchPictureResultsFullSynopsis(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].name == searchTerm)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

vector<Picture> searchPictureResultsPartialSynopsis(vector<Picture> vec, string searchTerm)
{
	vector<Picture> temp;
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i].name.find(searchTerm) != vec[i].name.npos)
		{
			temp.push_back(vec[i]);
		}
	}
	return(temp);
}

//Modify functions
void modifyPictureData(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to modify. Returning to main menu.\n" << endl;
		return;
	}

	vector<Picture> temp = searchPicture(pict);
	while (temp.size() > 1)
	{
		cout << "Too many results." << endl;
		switch (displayProceedConfirmation())
		{
		case 1:
			temp = searchPictureResults(temp);
			break;
		case 2:
			return;
			break;
		default:
			cout << "Invalid option given. Returning to main menu.\n" << endl;
			return;
		}
	}
	if (temp.size() == 0)
	{
		cout << "No elements to modify. Returning to main menu.\n" << endl;
	}
	else
	{
		modifyPictureNode(pict, temp[0]);
	}
}

vector<Picture> emptyPictureData()
{
	vector<Picture> temp;
	return(temp);
}

//Add data function
void addPictureNode(BSTreePicture* pict)
{
	//Flush the input stream
	cin.ignore();
	
	Picture temp = getNewPictureData();
	pict->addNode(temp.name, temp);
}

//Delete functions
void deletePictureNode(BSTreePicture* pict)
{
	if (!pictureSanityCheck(pict))
	{
		cout << "No data in Pictures to remove. Returning to main menu\n" << endl;
		return;
	}
	vector<Picture> temp;
	cout << "First, search for Picture(s) to remove." << endl;
	temp = searchPicture(pict);
	if (temp.size() == 0)
		return;
	cout << "Removing " << temp.size() << " elements from Pictures\n"
		<< "Elements to remove: " << endl;
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		printPicture(temp[i]);
		cout << endl;
	}
	switch (displayProceedConfirmation())
	{
	case 1:
		deleteSelectedNodes(pict, temp);
		break;
	case 2:
		return;
		break;
	default:
		cout << "Invalid input given. Returning to main menu.\n" << endl;
		return;
	}
}

Picture changePictureFields(Picture pict)
{
	string str;
	while (true)
	{
		switch (displayModifyPictureOptions())
		{
		case 1:
			cout << "Enter new name: ";
			getline(cin, str);
			pict.name = str;
			break;
		case 2:
			switch (displayMonthOptions())
			{
			case 1:
				pict.release = "January";
				break;
			case 2:
				pict.release = "February";
				break;
			case 3:
				pict.release = "March";
				break;
			case 4:
				pict.release = "April";
				break;
			case 5:
				pict.release = "May";
				break;
			case 6:
				pict.release = "June";
				break;
			case 7:
				pict.release = "July";
				break;
			case 8:
				pict.release = "August";
				break;
			case 9:
				pict.release = "September";
				break;
			case 10:
				pict.release = "October";
				break;
			case 11:
				pict.release = "November";
				break;
			case 12:
				pict.release = "December";
				break;
			default:
				pict.release = "";
			}
			break;
		case 3:
			str = "-1";
			while (str.find_first_not_of("0123456789") != str.npos)
			{
				cout << "Enter new release year (enter 0 if unknown): ";
				getline(cin, str);
				if (str.find_first_not_of("0123456789") != str.npos)
				{
					cout << "Please enter a number only." << endl;
				}
			}
			if (str == "")
			{
				pict.year = 0;
			}
			else
			{
				pict.year = stoi(str);
			}
			break;
		case 4:
			str = "-1";
			while (str.find_first_not_of("0123456789") != str.npos)
			{
				cout << "Enter new duration (enter 0 if unknown): ";
				getline(cin, str);
				if (str.find_first_not_of("0123456789") != str.npos)
				{
					cout << "Please enter a number only." << endl;
				}
			}
			if (str == "")
			{
				pict.duration = 0;
			}
			else
			{
				pict.duration = stoi(str);
			}
			break;
		case 5:
			cout << "Enter new genre 1: ";
			getline(cin, str);
			pict.genre1 = str;
			break;
		case 6:
			cout << "Enter new genre 2: ";
			getline(cin, str);
			pict.genre2 = str;
		case 7:
			str = "-1";
			while (str.find_first_not_of("0123456789") != str.npos)
			{
				cout << "Enter new number of nominations: ";
				getline(cin, str);
				if (str.find_first_not_of("0123456789") != str.npos)
				{
					cout << "Please enter a number only." << endl;
				}
			}
			if (str == "")
			{
				pict.nominations = 0;
			}
			else
			{
				pict.nominations = stoi(str);
			}
			break;
		case 8:
			str = "-1";
			while (str.find_first_not_of("0123456789.") != str.npos)
			{
				cout << "Enter new duration (enter 0 if unknown): ";
				getline(cin, str);
				if (str.find_first_not_of("0123456789") != str.npos)
				{
					cout << "Please enter a number only." << endl;
				}
			}
			if (str == "")
			{
				pict.rating = 0;
			}
			else
			{
				pict.rating = stod(str);
			}
			break;
		case 9:
			str = "-1";
			while (str.find_first_not_of("0123456789") != str.npos)
			{
				cout << "Enter new Metacritic score: ";
				getline(cin, str);
				if (str.find_first_not_of("0123456789") != str.npos)
				{
					cout << "Please enter a number only." << endl;
				}
			}
			if (str == "")
			{
				pict.metacritic = 0;
			}
			else
			{
				pict.metacritic = stoi(str);
			}
			break;
		case 10:
			cout << "Enter new genre 1: ";
			getline(cin, str);
			pict.synopsis = str;
			break;
		case 11:
			return(pict);
			break;
		default:
			cout << "Invalid option entered. Returning.\n" << endl;
			return(pict);
		}
	}
}

void deleteSelectedNodes(BSTreePicture* pict, const vector<Picture>& vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		NodePicture* temp = new NodePicture;
		temp = pict->findNode(vec[i].name);
		if (temp != nullptr)
		{
			if (temp->Data() == vec[i])
			{
				pict->deleteNode(temp->Key());
			}
		}
	}
}

bool defaultPicture(Picture pict)
{
	Picture temp;
	return(pict == temp);
}

void modifyPictureNode(BSTreePicture* tree, Picture pict)
{
	Picture temp = changePictureFields(pict);
	NodePicture* node = tree->findNode(pict.name);
	if (node == nullptr)
	{
		cout << "Could not find node. Returning.\n" << endl;
		return;
	}
	if (!(node->Data() == pict))
	{
		cout << "Unable to modify Picture data.\n" << endl;
		return;
	}
	else
	{
		tree->deleteNode(pict.name);
		tree->addNode(temp.name, temp);
	}
}

//Sort function (complete)
vector<Picture> sortPictures(BSTreePicture* treePict)
{
	if (!pictureSanityCheck(treePict))
	{
		cout << "No data in Pictures to sort. Returning to main menu.\n" << endl;
		return(emptyPictureData());
	}
	vector<Picture> temp;

	switch (displayPictureSortOptions())
	{
	case 1:
		return(treePict->sortByName(treePict->Root()));
		break;
	case 2:
		return(treePict->sortByRelease(treePict->Root()));
		break;
	case 3:
		return(treePict->sortByYear(treePict->Root()));
		break;
	case 4:
		return(treePict->sortByDuration(treePict->Root()));
		break;
	case 5:
		return(treePict->sortByNominations(treePict->Root()));
		break;
	case 6:
		return(treePict->sortByGenre1(treePict->Root()));
		break;
	case 7:
		return(treePict->sortByGenre2(treePict->Root()));
		break;
	case 8:
		return(treePict->sortByRating(treePict->Root()));
		break;
	case 9:
		return(treePict->sortByMetacritic(treePict->Root()));
		break;
	case 10:
		return(treePict->sortBySynopsis(treePict->Root()));
		break;
	default:
		cout << "Invalid option entered. Returning unsorted.\n" << endl;
		treePict->buildVector(treePict->Root(), temp);
		return(temp);
	}
}

//Sort Functions (results)
vector<Picture> sortPictures(const vector<Picture>& pict)
{
	switch (displayPictureSortOptions())
	{
	case 1:
		return(sortByPictureName(pict));
		break;
	case 2:
		return(sortByPictureRelease(pict));
		break;
	case 3:
		return(sortByPictureYear(pict));
		break;
	case 4:
		return(sortByPictureDuration(pict));
		break;
	case 5:
		return(sortByPictureNominations(pict));
		break;
	case 6:
		return(sortByPictureGenre1(pict));
		break;
	case 7:
		return(sortByPictureGenre2(pict));
		break;
	case 8:
		return(sortByPictureRating(pict));
		break;
	case 9:
		return(sortByPictureMetacritic(pict));
		break;
	case 10:
		return(sortByPictureSynopsis(pict));
		break;
	default:
		cout << "Invalid option entered. Returning unsorted.\n" << endl;
		return(pict);
	}
}

//Functions for sorting search results
vector<Picture> sortByPictureName(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureName);
	return(vec);
}

vector<Picture> sortByPictureRelease(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureRelease);
	return(vec);
}

vector<Picture> sortByPictureYear(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureYear);
	return(vec);
}

vector<Picture> sortByPictureDuration(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureDuration);
	return(vec);
}

vector<Picture> sortByPictureNominations(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureNominations);
	return(vec);
}

vector<Picture> sortByPictureGenre1(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureGenre1);
	return(vec);
}

vector<Picture> sortByPictureGenre2(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureGenre2);
	return(vec);
}

vector<Picture> sortByPictureRating(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureRating);
	return(vec);
}

vector<Picture> sortByPictureMetacritic(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureMetacritic);
	return(vec);
}

vector<Picture> sortByPictureSynopsis(vector<Picture> vec)
{
	sort(vec.begin(), vec.end(), comparePictureSynopsis);
	return(vec);
}

//Print functions
void printPicturesToFile(BSTreePicture* tree)
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
	printPictureHead(fout);
	tree->printFileInOrder(fout);
}

void printPictureHead(ostream& out)
{
	out << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis" << endl;
}
void printPicturesToFile(vector<Picture> vec)
{
	cin.ignore();
	bool fieldsToPrint[10] = { false, false, false, false, false, false, false, false, false, false };
	bool done = false;

	string str;
	ofstream fout;

	while (!done)
	{
		displayPictureCurrentChoices(fieldsToPrint);
		switch (displayPicturePrintOptions())
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
			fieldsToPrint[5] = !fieldsToPrint[5];
			break;
		case 7:
			fieldsToPrint[6] = !fieldsToPrint[6];
			break;
		case 8:
			fieldsToPrint[7] = !fieldsToPrint[7];
			break;
		case 9:
			fieldsToPrint[8] = !fieldsToPrint[8];
			break;
		case 10:
			fieldsToPrint[9] = !fieldsToPrint[9];
			break;
		case 11:
			done = true;
			break;
		default:
			cout << "Invalid input given. Aborting.\n" << endl;
			return;
		} //switch
	} //while

	done = false;
	while (!done)
	{
		str = getFileNameChoice();
		if (fileExists(str))
		{
			fileExistsWarning();
			switch (displayProceedConfirmation())
			{
			case 1:
				fout.open(str);
				if (fout.fail())
				{
					cout << "Error opening output file. Please try again.\n" << endl;
				}
				else
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
			} //switch
		} //if
		else
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
	} //while

	
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		printPicture(fout, vec[i], fieldsToPrint);
	}
	fout.close();
}

//Printing Pictures in sections instead of a table, since synopses can make the report very
//difficult to read otherwise.
void printPicture(ofstream& fout, Picture pict, const bool fieldsToPrint[10])
{
	//Output Film Title
	if (fieldsToPrint[0])
	{
		fout << "Picture: " << pict.name << endl;
	}

	//Output Release Month
	if (fieldsToPrint[1])
	{
		fout << "Release Month: " << pict.release << endl;
	}

	//Output Release Year
	if (fieldsToPrint[2])
	{
		fout << "Release Year: " << pict.year << endl;
	}

	//Output Duration
	if (fieldsToPrint[3])
	{
		fout << "Duration: " << pict.duration << endl;
	}

	//Output Nominations
	if (fieldsToPrint[4])
	{
		fout << "Nominations: " << pict.nominations << endl;
	}

	//Output Genre1
	if (fieldsToPrint[5])
	{
		fout << "Genre 1: " << pict.genre1 << endl;
	}

	//Output Genre2
	if (fieldsToPrint[6])
	{
		fout << "Genre 2: " << pict.genre2 << endl;
	}

	//Output Rating
	if (fieldsToPrint[7])
	{
		fout << "Rating: " << pict.rating << endl;
	}

	//Output Metactritic
	if (fieldsToPrint[8])
	{
		fout << "Metacritic: " << pict.metacritic << endl;
	}

	//Output Synopsis
	if (fieldsToPrint[9])
	{
		fout << "Synopsis: " << pict.synopsis << endl;
	}

	fout << "------------------------------\n" << endl;
}

void printPicture(const Picture& pict)
{
	cout << pict.name << ',' << pict.year << ',' << pict.nominations << ',' 
		<< pict.rating << ',' << pict.duration << ',' << pict.genre1 << ','
		<< pict.genre2 << ',' << pict.release << ',' << pict.metacritic << ','
		<< pict.synopsis << endl;
}

void displayPictureCurrentChoices(const bool pictureFieldsToPrint[10])
{
	//Output Film Title
	if (pictureFieldsToPrint[0])
	{
		cout << "Picture" << endl;
	}

	if (pictureFieldsToPrint[1])
	{
		cout << "Release Month" << endl;
	}

	if (pictureFieldsToPrint[2])
	{
		cout << "Release Year" << endl;
	}

	if (pictureFieldsToPrint[3])
	{
		cout << "Duration" << endl;
	}

	if (pictureFieldsToPrint[4])
	{
		cout << "Nominations" << endl;
	}

	if (pictureFieldsToPrint[5])
	{
		cout << "Genre 1" << endl;
	}

	if (pictureFieldsToPrint[6])
	{
		cout << "Genre 2" << endl;
	}

	if (pictureFieldsToPrint[7])
	{
		cout << "Rating" << endl;
	}

	if (pictureFieldsToPrint[8])
	{
		cout << "Metacritic" << endl;
	}

	if (pictureFieldsToPrint[9])
	{
		cout << "Synopsis" << endl;
	}
	cout << endl;
}
