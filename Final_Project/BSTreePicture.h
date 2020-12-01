/* Gregory Wicklund
* Class: CSCI-2421
* Final Project BSTreePicture.h file
*/

//To be used in conjunction with Node.h and BSTreeInt.cpp
//If you modify this, please add your name and list any changes that you made
//Changes: Modified object types for an Picture object instead of an int
//Added functions are in their own section
#ifndef BSTREEPICTURE_
#define BSTREEPICTURE_

#include "NodePicture.h"
#include "Picture.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


// Binary Search Tree class
class BSTreePicture {
private:
	NodePicture* root;
	void addNode(string key, NodePicture* leaf, Picture act);
	NodePicture* deleteNode(NodePicture* node, string key);
	void freeNode(NodePicture* leaf);
	void printInorder(NodePicture* node);
	NodePicture* findNode(string key, NodePicture* parent);

	//Added functions and variables
	//This *should* keep track of the number of elements?
	int count = 0;
	void searchPartialPictureName(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchFullPictureName(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchPictureRelease(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchFullPictureYear(NodePicture* node, int searchKey, vector<Picture>& vec);
	void searchPartialPictureYear(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchFullPictureDuration(NodePicture* node, int searchKey, vector<Picture>& vec);
	void searchPartialPictureDuration(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchFullPictureGenre(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchPartialPictureGenre(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchFullPictureNominations(NodePicture* node, int searchKey, vector<Picture>& vec);
	void searchPartialPictureNominations(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchFullPictureRating(NodePicture* node, double searchKey, vector<Picture>& vec);
	void searchPartialPictureRating(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchFullPictureMetacritic(NodePicture* node, int searchKey, vector<Picture>& vec);
	void searchPartialPictureMetacritic(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchFullPictureSynopsis(NodePicture* node, string searchKey, vector<Picture>& vec);
	void searchPartialPictureSynopsis(NodePicture* node, string searchKey, vector<Picture>& vec);
	void printFileInOrder(ostream& out, NodePicture* aNode);
	//End Added functions

public:
	BSTreePicture();
	~BSTreePicture();
	NodePicture* Root() { return root; }
	void setRoot(NodePicture* _root) { root = _root; }
	void addNode(string key, Picture act);
	NodePicture* findNode(string key);
	void printInorder();
	void deleteNode(string key);
	NodePicture* min(NodePicture* node);
	NodePicture* max(NodePicture* node);

	//Added functions
	Picture readInput(ifstream& fin);
	void buildVector(NodePicture* node, vector<Picture>& vec);
	int getPictureCount() { return count; }
	void printPictureCount();
	void addCount() { count++; }
	void removeCount() { count--; }
	ostream& printPictureNode(ostream& out, const Picture& pict);

	//Search functions
	vector<Picture> searchFullPictureName(NodePicture* node, string searchKey);
	vector<Picture> searchPartialPictureName(NodePicture* node, string searchKey);
	vector<Picture> searchPictureRelease(NodePicture* node, string searchKey);
	vector<Picture> searchFullPictureYear(NodePicture* node, int searchKey);
	vector<Picture> searchPartialPictureYear(NodePicture* node, string searchKey);
	vector<Picture> searchFullPictureDuration(NodePicture* node, int searchKey);
	vector<Picture> searchPartialPictureDuration(NodePicture* node, string searchKey);
	vector<Picture> searchFullPictureGenre(NodePicture* node, string searchKey);
	vector<Picture> searchPartialPictureGenre(NodePicture* node, string searchKey);
	vector<Picture> searchFullPictureNominations(NodePicture* node, int searchKey);
	vector<Picture> searchPartialPictureNominations(NodePicture* node, string searchKey);
	vector<Picture> searchFullPictureRating(NodePicture* node, double searchKey);
	vector<Picture> searchPartialPictureRating(NodePicture* node, string searchKey);
	vector<Picture> searchFullPictureMetacritic(NodePicture* node, int searchKey);
	vector<Picture> searchPartialPictureMetacritic(NodePicture* node, string searchKey);
	vector<Picture> searchFullPictureSynopsis(NodePicture* node, string searchKey);
	vector<Picture> searchPartialPictureSynopsis(NodePicture* node, string searchKey);

	//Complete sort functions
	vector<Picture> sortByName(NodePicture* root);
	vector<Picture> sortByRelease(NodePicture* root);
	vector<Picture> sortByYear(NodePicture* root);
	vector<Picture> sortByDuration(NodePicture* root);
	vector<Picture> sortByGenre1(NodePicture* root);
	vector<Picture> sortByGenre2(NodePicture* root);
	vector<Picture> sortByNominations(NodePicture* root);
	vector<Picture> sortByRating(NodePicture* root);
	vector<Picture> sortByMetacritic(NodePicture* root);
	vector<Picture> sortBySynopsis(NodePicture* root);

	//Partial sort functions work on a vector of Picture structs, but don't
	//need access to any member variables, so they're declared outside the class.
	//End added functions
	void printFileInOrder(ostream& out);

};

#endif  //BST
