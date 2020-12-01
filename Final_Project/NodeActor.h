/* Gregory Wicklund
* Class: CSCI-2421
* Final Project NodeActor.h file
*/

//To be used in conjunction with BSTreeInt.h and BSTreeInt.cpp
//If you modify this, please add your name and list any changes that you made
//Changes made: Modified key datatype to string, made data's type Actor,
//Added equality operator.
#ifndef NODEACTOR_
#define NODEACTOR_
#include <iostream>
#include <string>
#include "ActorActress.h" //Gives Actor objects
using namespace std;

// A tree node for Actors and Actresses/Nominations.

//Binary Tree Node
class NodeActor {
private:
    string key; //This should be the datatype of your key...sorted field in tree
    Actor data;
    NodeActor* left;
    NodeActor* right;
    NodeActor* parent;
public:
    NodeActor() { key="-1"; left=nullptr; right=nullptr; parent = nullptr;};
	void setData(Actor aData) { data = aData; }; //Read in from istream to set data
    void setKey(string aKey) { key = aKey; };
    void setLeft(NodeActor* aLeft) { left = aLeft; };
    void setRight(NodeActor* aRight) { right = aRight; };
    void setParent(NodeActor* aParent) { parent = aParent; };
	string Key() { return key; };
	Actor Data() { return data; };
    NodeActor* Left() { return left; };
    NodeActor* Right() { return right; };
    NodeActor* Parent() { return parent; };
};

#endif
