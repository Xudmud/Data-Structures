/*	Gregory Wicklund
	CSCI2421 Final Project
	PictureFunctions.h file
	This file is virtually identical to ActorFunctions.h,
	though adapted to handle Picture objects.*/
#ifndef PICTUREFUNCTIONS_
#define PICTUREFUNCTIONS_

#include "BSTreePicture.h"
#include "Picture.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>


//Read functions
void readPicturesIn(string fileChoice, BSTreePicture* pictAct);
Picture getNewPictureData();

//Check if the tree has data.
bool pictureSanityCheck(BSTreePicture* act);

//Main search function
vector<Picture> searchPicture(BSTreePicture* treePict);

//Result search functions
vector<Picture> searchPictureResults(vector<Picture> vec);
vector<Picture> searchPictureResultsName(vector<Picture> vec);
vector<Picture> searchPictureResultsFullName(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsPartialName(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsYear(vector<Picture> vec);
vector<Picture> searchPictureResultsFullYear(vector<Picture> vec, int searchTerm);
vector<Picture> searchPictureResultsPartialYear(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsNominations(vector<Picture> vec);
vector<Picture> searchPictureResultsFullNominations(vector<Picture> vec, int searchTerm);
vector<Picture> searchPictureResultsPartialNominations(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsRating(vector<Picture> vec);
vector<Picture> searchPictureResultsFullRating(vector<Picture> vec, double searchTerm);
vector<Picture> searchPictureResultsPartialRating(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsDuration(vector<Picture> vec);
vector<Picture> searchPictureResultsFullDuration(vector<Picture> vec, int searchTerm);
vector<Picture> searchPictureResultsPartialDuration(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsGenre(vector<Picture> vec);
vector<Picture> searchPictureResultsFullGenre(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsPartialGenre(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsRelease(vector<Picture> vec);
vector<Picture> searchPictureResultsRelease(vector<Picture> vec, string searchTerm); //search by month
vector<Picture> searchPictureResultsMetacritic(vector<Picture> vec);
vector<Picture> searchPictureResultsFullMetacritic(vector<Picture> vec, int searchTerm);
vector<Picture> searchPictureResultsPartialMetacritic(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsSynopsis(vector<Picture> vec);
vector<Picture> searchPictureResultsFullSynopsis(vector<Picture> vec, string searchTerm);
vector<Picture> searchPictureResultsPartialSynopsis(vector<Picture> vec, string searchTerm);

//Tree Search Functions (starters, get field to search and search term)
vector<Picture> searchPictureName(BSTreePicture* pict);
vector<Picture> searchPictureYear(BSTreePicture* pict);
vector<Picture> searchPictureNominations(BSTreePicture* pict);
vector<Picture> searchPictureRating(BSTreePicture* pict);
vector<Picture> searchPictureRelease(BSTreePicture* pict);
vector<Picture> searchPictureDuration(BSTreePicture* pict);
vector<Picture> searchPictureGenre(BSTreePicture* pict);
vector<Picture> searchPictureMetacritic(BSTreePicture* pict);
vector<Picture> searchPictureSynopsis(BSTreePicture* pict);
void modifyPictureData(BSTreePicture* pict);
Picture changePictureFields(Picture pict);
vector<Picture> emptyPictureData();

//manipulate functions
void addPictureNode(BSTreePicture* pict);
void deletePictureNode(BSTreePicture* pict);
void deleteSelectedNodes(BSTreePicture* pict, const vector<Picture>& vec);
bool defaultPicture(Picture pict);
void modifyPictureNode(BSTreePicture* tree, Picture pict);

//Sort functions
vector<Picture> sortPictures(BSTreePicture* treePict);
vector<Picture> sortPictures(const vector<Picture>& pict);

//Search result sort functions
vector<Picture> sortByPictureName(vector<Picture> vec);
vector<Picture> sortByPictureYear(vector<Picture> vec);
vector<Picture> sortByPictureNominations(vector<Picture> vec);
vector<Picture> sortByPictureRating(vector<Picture> vec);
vector<Picture> sortByPictureDuration(vector<Picture> vec);
vector<Picture> sortByPictureGenre1(vector<Picture> vec);
vector<Picture> sortByPictureGenre2(vector<Picture> vec);
vector<Picture> sortByPictureRelease(vector<Picture> vec);
vector<Picture> sortByPictureMetacritic(vector<Picture> vec);
vector<Picture> sortByPictureSynopsis(vector<Picture> vec);

//print functions
void printPictureHead(ostream& out);
void printPicturesToFile(BSTreePicture* tree);
void printPicturesToFile(vector<Picture> vec);
void displayPictureCurrentChoices(const bool pictureFieldsToPrint[10]);

void printPicture(const Picture& pict);
void printPicture(ofstream& fout, Picture pict, const bool fieldsToPrint[10]);

#endif