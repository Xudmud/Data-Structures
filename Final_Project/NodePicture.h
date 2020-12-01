/* Gregory Wicklund
* Class: CSCI-2421
* Final Project NodePicture.h file
*/
//To be used in conjunction with BSTreeInt.h and BSTreeInt.cpp
//If you modify this, please add your name and list any changes that you made
//Changed: changed key's datatype to string, changed data's datatype to Picture, added opeators
#ifndef NODEPICTURE_
#define NODEPICTURE_
#include <iostream>
#include "Picture.h" //Gives Picture access
#include <string>
using namespace std;

//Binary Tree Node
class NodePicture {
private:
	string key; //This should be the datatype of your key...sorted field in tree
	Picture data;
	NodePicture* left;
	NodePicture* right;
	NodePicture* parent;
public:
	NodePicture() { key = "-1"; left = nullptr; right = nullptr; parent = nullptr; };
	void setData(Picture aData) { data = aData; }; //Read in from istream to set data
	void setKey(string aKey) { key = aKey; };
	void setLeft(NodePicture* aLeft) { left = aLeft; };
	void setRight(NodePicture* aRight) { right = aRight; };
	void setParent(NodePicture* aParent) { parent = aParent; };
	string Key() { return key; };
	Picture Data() { return data; };
	NodePicture* Left() { return left; };
	NodePicture* Right() { return right; };
	NodePicture* Parent() { return parent; };
};


#endif
