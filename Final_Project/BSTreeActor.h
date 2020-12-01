/* Gregory Wicklund
* Class: CSCI-2421
* Final Project BSTreeActor.h file
*/

//To be used in conjunction with Node.h and BSTreeInt.cpp
//If you modify this, please add your name and list any changes that you made
//Changes: Modified object types for an Actor object instead of an int
//Added functions are in their own section
//(I may have missed a couple modified sections in the given functions, but I did my best to mark the changes I made.)
#ifndef BSTREEACTOR_
#define BSTREEACTOR_

#include "NodeActor.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


// Binary Search Tree class
class BSTreeActor {
private:
	NodeActor* root;
	void addNode(string key, NodeActor* leaf, Actor act);
	NodeActor* deleteNode(NodeActor* node, string key);
	void freeNode(NodeActor* leaf);
	void printInorder(NodeActor* node);
	NodeActor* findNode(string key, NodeActor* parent);

	//Added functions and variables
	//This *should* keep track of the number of elements?
	int count = 0;
	void searchPartialActorName(NodeActor* node, string searchKey, vector<Actor>& vec);
	void searchFullActorName(NodeActor* node, string searchKey, vector<Actor>& vec);
	void searchFullFilm(NodeActor* node, string searchKey, vector<Actor>& vec);
	void searchPartialFilm(NodeActor* node, string searchKey, vector<Actor>& vec);
	void searchFullYear(NodeActor* node, int searchKey, vector<Actor>& vec);
	void searchPartialYear(NodeActor* node, string searchKey, vector<Actor>& vec);
	void searchFullAward(NodeActor* node, string searchKey, vector<Actor>& vec);
	void searchPartialAward(NodeActor* node, string searchKey, vector<Actor>& vec);
	void searchActorWin(NodeActor* node, vector<Actor>& vec);
	void searchActorLose(NodeActor* node, vector<Actor>& vec);
	ostream& printActorNode(ostream& out, const Actor& act);
	void printFileInOrder(ostream& out, NodeActor* node);
	//End Added functions

public:
	BSTreeActor();
	~BSTreeActor();
	NodeActor* Root() { return root; }
	void setRoot(NodeActor* _root) { root = _root; }
	void addNode(string key, Actor act);
	NodeActor* findNode(string key);
	void printInorder();
	void deleteNode(string key);
	NodeActor* min(NodeActor* node);
	NodeActor* max(NodeActor* node);

	//Added functions
	Actor readInput(ifstream& fin);
	void buildVector(NodeActor* node, vector<Actor>& vec);
	int getActorCount() { return count; }
	void printActorCount();
	void addCount() { count++; }
	void removeCount() { count--; }
	//Search functions
	vector<Actor> searchFullActorName(NodeActor* node, string searchKey);
	vector<Actor> searchPartialActorName(NodeActor* node, string searchKey);
	vector<Actor> searchFullFilm(NodeActor* node, string searchKey);
	vector<Actor> searchPartialFilm(NodeActor* node, string searchKey);
	vector<Actor> searchFullYear(NodeActor* node, int searchKey);
	vector<Actor> searchPartialYear(NodeActor* node, string searchKey);
	vector<Actor> searchFullAward(NodeActor* node, string searchKey);
	vector<Actor> searchPartialAward(NodeActor* node, string searchKey);
	vector<Actor> searchWinLose(NodeActor* node, bool win);

	//Complete sort functions
	vector<Actor> sortByName(NodeActor* root);
	vector<Actor> sortByFilm(NodeActor* root);
	vector<Actor> sortByYear(NodeActor* root);
	vector<Actor> sortByAward(NodeActor* root);
	vector<Actor> sortByWinner(NodeActor* root); //Not sure this one is needed

	//Partial sort functions work on a vector of Actor structs, but don't
	//need access to any member variables, so they're declared outside the class.

	//File print function
	void printFileInOrder(ostream& out);
	//End added functions

};

#endif  //BST
