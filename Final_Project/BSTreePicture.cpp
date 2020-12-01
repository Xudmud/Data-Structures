/* Gregory Wicklund
* CSCI 2421
* Final Project: BSTreePicture.cpp file
* Changes made:
* -Completed the addNode(int key), addNode(Node* leaf, int key), findNode(int key, Node* node),
*	and printInorder() functions; changed data types for Actor objects.
* -Modified the deleteNode(Node* root, int key) function to correct an access violation error
*	that occurred if run in its original state.
* -Changed function declarations, namespaces, and parameters to account for a key of type string
and the class being BSTreeActor.
* Added functions are notated in their own section.*/




//To be used in conjunction with BSTreeInt.h and BSTreeInt.cpp
//When you modify this, please add your name and list any changes that you made
//A few member functions have been left blank so you, the student can implemement



#include "BSTreePicture.h"
#include "PictureFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Constructor
BSTreePicture::BSTreePicture() {
	root = new NodePicture;
}

// Destructor
BSTreePicture::~BSTreePicture() {
	if (root != nullptr)
		freeNode(root);
}



// Free the node
void BSTreePicture::freeNode(NodePicture* leaf)
{
	if (this->Root() == leaf)
	{
		delete leaf;
	}
	else if (leaf != nullptr)

	{
		freeNode(leaf->Left());
		freeNode(leaf->Right());
		delete leaf;
	}

}

// Add a node
void BSTreePicture::addNode(string key, Picture pic)
{
	if (defaultPicture(pic)) //Picture object is empty, no need to add. Do nothing and return.
		return;
	//Check if root is nullptr, if so set the root and add the key.
	if (root == nullptr)
	{
		//Create a new node, add the key. Left, right, and parent get set to nullptr by the constructor.
		root = new NodePicture;
		root->setKey(key);
		root->setData(pic);
	}
	else if (root->Key() == "-1") //Might need a different test value
	{
		root->setKey(key);
		root->setData(pic);
		//Left(), Right(), and Parent() are set to nullptr by the constructor.
	}
	//left and right get set to nullptr already by the constructor.

	//Start navigating the tree to add the node.
	else if (key < root->Key())
	{
		//Check if left node is null
		if (root->Left() == nullptr)
			//Add a new node to the left.
		{
			NodePicture* tempnode = new NodePicture;
			tempnode->setKey(key);
			tempnode->setData(pic);
			//left and right get set to nullptr, need to set parent.
			//In this case, it's root.
			tempnode->setParent(root);
			//Set root's left to the new node.
			root->setLeft(tempnode);
		}
		else
		{
			//Call the recursive function, which will treat root's left as "root"
			addNode(key, root->Left(), pic);
		}
	}

	else //key is greater than or equal, go right.
	{
		//Check if right node is null.
		if (root->Right() == nullptr)
		{
			NodePicture* tempnode = new NodePicture;
			tempnode->setKey(key);
			tempnode->setData(pic);
			tempnode->setParent(root);
			root->setRight(tempnode);
		}
		else
		{
			addNode(key, root->Right(), pic);
		}
	}
	addCount();
	//Student must fill in
	//Base Case: No elements. Add the root and set the key
	//Otherwise use recursive (private) addNode

}

// Add a node (private)
void BSTreePicture::addNode(string key, NodePicture* leaf, Picture pic)
{
	//Check if the key is less than the current leaf.
	if (key < leaf->Key())
	{
		//If so, key is less and goes on the left.
		//Check if the next leaf on left is null.
		if (leaf->Left() == nullptr)
		{
			//If so, crate a new node, add the information.
			NodePicture* tempnode = new NodePicture;
			//tempnode's key is the passed key value.
			tempnode->setKey(key);
			tempnode->setData(pic);
			//tempnode's parent should be the leaf.
			tempnode->setParent(leaf);
			//As the key's value is less, assign the node to the left.
			leaf->setLeft(tempnode);
			//The right node is already set to nullptr by the constructor
		} //if
		  //Otherwise, call addNode(key, leaf->Left()) to traverse one leaf down.
		else
		{
			addNode(key, leaf->Left(), pic);
		} //else
	} //if
	  //Else, the key must be greater than or equal to the leaf's key. Check if the leaf's right branch is null.
	else
	{
		if (leaf->Right() == nullptr)
		{
			//If so, set the key's right branch to the key, and set the parent node. Then attach the node to the right of the leaf.
			NodePicture* tempnode = new NodePicture;
			tempnode->setKey(key);
			tempnode->setData(pic);
			tempnode->setParent(leaf);
			leaf->setRight(tempnode);
		} //if
		else
		{
			//Otherwise, call addNode(key, leaf->Right()) to traverse one leaf down
			addNode(key, leaf->Right(), pic);
		} //else
	} //if



	  //Student must fill in
	  //Don't forget to set your key, Parent, then left or right
	  //Based on the case you use you will addNode recursively to the left or right

}

NodePicture* BSTreePicture::findNode(string key)
{
	return findNode(key, root);
}

// Find a node
NodePicture* BSTreePicture::findNode(string key, NodePicture* node)
{
	//check for nullptr as the first element. This is needed to prevent a nullptr reference.
	if (node == nullptr)
	{
		return(nullptr);
	}
	//Check if we've found the key
	if (node->Key() == key)
	{
		return (node);
	}
	//Key isn't found, check if it's less
	else if (key < node->Key())
	{
		if (node->Left() == nullptr)
		{
			return(nullptr);
		}
		else
		{
			return(findNode(key, node->Left()));
		}
	}
	//Key should be greater, so go right now
	else
	{
		if (node->Right() == nullptr)
		{
			return(nullptr);
		}
		else
		{
			return(findNode(key, node->Right()));
		}
	}
	//Student must fill in
	// trap nullptr first in case we've hit the end unsuccessfully.
	// success base case
	//Greater than (Right), Less than (Left)

}

void BSTreePicture::printInorder()
{
	printInorder(root);
}

void BSTreePicture::printInorder(NodePicture* aNode)
{
	//Code taken from in-class BSTreeint.cpp example.
	/*******************************************/
	if (aNode != nullptr)
	{
		if (aNode->Left() != nullptr)
			printInorder(aNode->Left());
		if (aNode->Key() != "-1")
			//Need a separate function to handle the print because of c++ left-to-right rule.
			printPictureNode(cout, aNode->Data());
		if (aNode->Right() != nullptr)
			printInorder(aNode->Right());
	}
	/********************************************/
	//Student must fill in.  Use recursive algorithm.
	//Note that this prints using an Inorder, Depth-first search
	//but you may want to do something else when "visiting" the node....
	//like moving visited data to another datastructure
	//Don't forget your base case!
}

void BSTreePicture::printFileInOrder(ostream& out)
{
	printFileInOrder(out, root);
}

void BSTreePicture::printFileInOrder(ostream& out, NodePicture* aNode)
{
	if (aNode != nullptr)
	{
		if (aNode->Left() != nullptr)
			printFileInOrder(out, aNode->Left());
		if (!defaultPicture(aNode->Data()))
			printPictureNode(out, aNode->Data());
		if (aNode->Right() != nullptr)
			printFileInOrder(out, aNode->Right());
	}
}

void BSTreePicture::deleteNode(string key)
{
	{
		if (deleteNode(Root(), key) == nullptr)
			setRoot(nullptr);
	}
}

//deleteNode (Private)
NodePicture* BSTreePicture::deleteNode(NodePicture* root, string key)
{

	/* Given a binary search tree and a key, this function deletes the key
	and returns the new root */

	//Modified by Gregory Wicklund. Changed the implementation for Case 2 to avoid memory access violations. It now creates
	//a temporary node for the right or left leaf, updates root's key with that leaf's value, and then root's right and left
	//branch with the right and left branch of the temp node. Last, it deletes the temp node. The original functions appear
	//to have been intended to accomplish the same thing, but lost access to a pointer, which caused an access violation
	//as the tree was emptied. The code was reasoned out, based on what was needed to be accomplished and what the original
	//code was trying to do.

	if (root == nullptr) return root;
	else if (key < root->Key())
		root->setLeft(deleteNode(root->Left(), key));
	else if (key > root->Key())
		root->setRight(deleteNode(root->Right(), key));
	else {
		// Case 1: No Child
		if (root->Left() == nullptr && root->Right() == nullptr) {
			delete root;
			root = nullptr;
			// Case 2: one child
		}
		else if (root->Left() == nullptr) {
			/*********Changed this portion***************/
			//Set a temp node equal to root's right
			NodePicture* temp = root->Right();
			//Set root's key to the right node's key
			root->setKey(temp->Key());
			root->setData(temp->Data());
			//Set right and left pointers, to gather any additional nodes as needed.
			//Set right to be temp's right. Any nodes attached to right stay attached to right.
			root->setRight(temp->Right());
			//Set left to be right's left. ANy nodes attached to left stay attached to left.
			root->setLeft(temp->Left());
			//We're done with temp node, and it can be safely deleted.
			delete temp;
			//At this point, the right-hand node is now where root was, with its nodes adjusted as needed.
			/*******************************************/

			/*Original Code
			* Node *temp = root;
			* root = root->Right();
			* delete temp;
			*/

		}
		else if (root->Right() == nullptr) {
			/*********Changed this portion***************/
			//Same process as the above case, except working with the left leaf instead of the right.
			NodePicture* temp = root->Left();
			root->setKey(temp->Key());
			root->setData(temp->Data());
			root->setLeft(temp->Left());
			root->setRight(temp->Right());
			delete temp;
			/*******************************************/
			/*Original Code
			* Node *temp = root;
			* root = root->Left();
			* delete temp;
			*/
		}
		else {
			NodePicture *temp = min(root->Right());
			root->setKey(temp->Key());
			root->setData(temp->Data());
			root->setRight(deleteNode(root->Right(), temp->Key()));
		}
	}
	//At this point root should be returned. But for some reason it isn't happening that way.
	return root;
}


// Find the node with min key
// Traverse the left sub-BSTree recursively
// till left sub-BSTree is empty to get min
NodePicture* BSTreePicture::min(NodePicture* node)
{
	NodePicture* tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Left())
	{
		tempNode = min(node->Left());
	}
	else
		tempNode = node;

	return tempNode;
}

// Find the node with max key
// Traverse the right sub-BSTree recursively
// till right sub-BSTree is empty to get max
NodePicture* BSTreePicture::max(NodePicture* node)
{
	NodePicture * tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Right())
		tempNode = max(node->Right());
	else
		tempNode = node;

	return tempNode;
}

//Added functions
Picture BSTreePicture::readInput(ifstream& fin)
{
	Picture temp;
	string str;
	//Read name (string)
	if (fin.peek() == '\"')
	{
		fin.ignore();
		getline(fin, str, '\"');
		fin.ignore();
	}
	else
	{
		getline(fin, str, ',');
	}
	temp.name = str;

	//Read year (int)
	getline(fin, str, ',');
	if (str != "" && str.find_first_not_of("0123456789") == str.npos)
	{
		temp.year = stoi(str);
	}
	else
	{
		temp.year = 0;
	}

	//Read nominations (int)
	getline(fin, str, ',');
	if (str != "" && str.find_first_not_of("0123456789") == str.npos)
	{
		temp.nominations = stoi(str);
	}
	else
	{
		temp.nominations = 0;
	}

	//Read rating (double)
	getline(fin, str, ',');
	if (str != "" && str.find_first_not_of("0123456789.") == str.npos)
	{
		temp.rating = stod(str);
	}
	else
	{
		temp.rating = 0;
	}

	//Read duration (int)
	getline(fin, str, ',');
	if (str != "" && str.find_first_not_of("0123456789") == str.npos)
	{
		temp.duration = stoi(str);
	}
	else
	{
		temp.duration = 0;
	}

	//Read genre1 (string)
	if (fin.peek() == '\"')
	{
		fin.ignore();
		getline(fin, str, '\"');
		fin.ignore();
	}
	else
	{
		getline(fin, str, ',');
	}
	temp.genre1 = str;
	
	//Read genre2 (string)
	if (fin.peek() == '\"')
	{
		fin.ignore();
		getline(fin, str, '\"');
		fin.ignore();
	}
	else
	{
		getline(fin, str, ',');
	}
	temp.genre2 = str;

	//Read release (string)
	if (fin.peek() == '\"')
	{
		fin.ignore();
		getline(fin, str, '\"');
		fin.ignore();
	}
	else
	{
		getline(fin, str, ',');
	}
	temp.release = str;

	//Read metacritic (int)
	//Read synopsis (synopsis)
	if (fin.peek() == '\"')
	{
		fin.ignore();
		getline(fin, str);
		str.pop_back();
	}
	else
	{
		getline(fin, str);
	}
	str.replace(str.begin(), str.end(), "\"\"", "\""); //Should change instances of ""foo"" to "foo"
	temp.synopsis = str;
	


	//Return the Picture object, which is used for the data of the NodeActor object.
	return(temp);
}

void BSTreePicture::printPictureCount()
{
	cout << "There are currently " << count << " elements in the database.\n" << endl;
}

vector<Picture> BSTreePicture::searchFullPictureName(NodePicture* node, string searchKey)
{
	//Since the actor's name is the key, the search can just use key.
	vector<Picture> vec;
	if (node == nullptr) //Base case, in case the tree is empty.
	{
		return(vec);
	}
	else
	{
		searchFullPictureName(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchFullPictureName(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr) //We've reached the end of the tree
	{
		return;
	}
	if (node->Key() == searchKey)
	{
		//Add the result to the node.
		vec.push_back(node->Data());
		//Any further results will be to the right, so call recursively to the right.
		searchFullPictureName(node->Right(), searchKey, vec);
	}
	else if (searchKey < node->Key())
	{
		if (node->Left() == nullptr)
		{
			return;
		}
		else
		{
			searchFullPictureName(node->Left(), searchKey, vec);
		}
	}
	else //Key must be greater, go right.
	{
		if (node->Right() == nullptr)
		{
			return;
		}
		else
		{
			searchFullPictureName(node->Right(), searchKey, vec);
		}
	}
}

vector<Picture> BSTreePicture::searchPartialPictureName(NodePicture* node, string searchKey)
{
	//Since the actor's name is the key, the search can just use keys.
	//Partial search needs to search every node, since partial matches could be to the left or right.
	//Code adapted from the printInOrder() function.
	vector<Picture> vec;
	if (node == nullptr) //Base case, in case the tree is empty.
	{
		return(vec);
	}
	else
	{
		searchPartialPictureName(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPartialPictureName(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	//Need to search the entire tree, since some results could fall on either side of any given node.
	//Search left (if applicable)
	if (node->Left() != nullptr)
	{
		searchPartialPictureName(node->Left(), searchKey, vec);
	}
	//Search current

	//Check if node's partial key matches the partial search.
	if (node->Key().find(searchKey) != node->Key().npos)
	{
		//Add the Actor object if it is.
		vec.push_back(node->Data());
	}
	//Search right
	if (node->Right() != nullptr)
	{
		searchPartialPictureName(node->Right(), searchKey, vec);
	}
	//Vector was passed by reference, no need to return it here.
}

//Search Picture Release
//Since this is by month, there's no need for a partial search.
vector<Picture> BSTreePicture::searchPictureRelease(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPictureRelease(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPictureRelease(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchPictureRelease(node->Left(), searchKey, vec);
	}
	if (node->Data().release == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPictureRelease(node->Right(), searchKey, vec);
	}
}

//Search Picture Year (int)
vector<Picture> BSTreePicture::searchFullPictureYear(NodePicture* node, int searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullPictureYear(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchFullPictureYear(NodePicture* node, int searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchFullPictureYear(node->Left(), searchKey, vec);
	}
	if (node->Data().year == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullPictureYear(node, searchKey, vec);
	}
}

vector<Picture> BSTreePicture::searchPartialPictureYear(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialPictureYear(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPartialPictureYear(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchPartialPictureYear(node->Left(), searchKey, vec);
	}
	if (to_string(node->Data().year).find(searchKey) != to_string(node->Data().year).npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialPictureYear(node->Right(), searchKey, vec);
	}
}

//Search Picture Duration (int)
vector<Picture> BSTreePicture::searchFullPictureDuration(NodePicture* node, int searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullPictureDuration(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchFullPictureDuration(NodePicture* node, int searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchFullPictureDuration(node->Left(), searchKey, vec);
	}
	if (node->Data().duration == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullPictureDuration(node, searchKey, vec);
	}
}

vector<Picture> BSTreePicture::searchPartialPictureDuration(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialPictureDuration(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPartialPictureDuration(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchPartialPictureDuration(node->Left(), searchKey, vec);
	}
	if (to_string(node->Data().duration).find(searchKey) != to_string(node->Data().duration).npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialPictureDuration(node->Right(), searchKey, vec);
	}
}

//Search Picture Genre (both at once)
vector<Picture> BSTreePicture::searchFullPictureGenre(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullPictureGenre(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchFullPictureGenre(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchFullPictureGenre(node->Left(), searchKey, vec);
	}
	if (node->Data().genre1 == searchKey || node->Data().genre2 == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullPictureGenre(node, searchKey, vec);
	}
}

vector<Picture> BSTreePicture::searchPartialPictureGenre(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialPictureGenre(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPartialPictureGenre(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchPartialPictureGenre(node->Left(), searchKey, vec);
	}
	if (node->Data().genre1.find(searchKey) != node->Data().genre1.npos || node->Data().genre2.find(searchKey) != node->Data().genre2.npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialPictureGenre(node->Right(), searchKey, vec);
	}
}

//Search Picture Nominations (int)
vector<Picture> BSTreePicture::searchFullPictureNominations(NodePicture* node, int searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullPictureNominations(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchFullPictureNominations(NodePicture* node, int searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchFullPictureNominations(node->Left(), searchKey, vec);
	}
	if (node->Data().nominations == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullPictureNominations(node, searchKey, vec);
	}
}

vector<Picture> BSTreePicture::searchPartialPictureNominations(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialPictureNominations(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPartialPictureNominations(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchPartialPictureNominations(node->Left(), searchKey, vec);
	}
	if (to_string(node->Data().nominations).find(searchKey) != to_string(node->Data().nominations).npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialPictureNominations(node->Right(), searchKey, vec);
	}
}

//Search Picture Rating (double)
vector<Picture> BSTreePicture::searchFullPictureRating(NodePicture* node, double searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullPictureRating(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchFullPictureRating(NodePicture* node, double searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchFullPictureRating(node->Left(), searchKey, vec);
	}
	if (node->Data().rating == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullPictureRating(node, searchKey, vec);
	}
}

vector<Picture> BSTreePicture::searchPartialPictureRating(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialPictureRating(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPartialPictureRating(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchPartialPictureRating(node->Left(), searchKey, vec);
	}
	if (to_string(node->Data().rating).find(searchKey) != to_string(node->Data().rating).npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialPictureRating(node->Right(), searchKey, vec);
	}
}

//Search Picture Metacritic (int)
vector<Picture> BSTreePicture::searchFullPictureMetacritic(NodePicture* node, int searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullPictureMetacritic(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchFullPictureMetacritic(NodePicture* node, int searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchFullPictureMetacritic(node->Left(), searchKey, vec);
	}
	if (node->Data().metacritic == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullPictureMetacritic(node, searchKey, vec);
	}
}

vector<Picture> BSTreePicture::searchPartialPictureMetacritic(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialPictureMetacritic(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPartialPictureMetacritic(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchPartialPictureMetacritic(node->Left(), searchKey, vec);
	}
	if (to_string(node->Data().metacritic).find(searchKey) != to_string(node->Data().metacritic).npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialPictureMetacritic(node->Right(), searchKey, vec);
	}
}

//Search Picture Synopsis (string)
vector<Picture> BSTreePicture::searchFullPictureSynopsis(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullPictureSynopsis(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchFullPictureSynopsis(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchFullPictureSynopsis(node->Left(), searchKey, vec);
	}
	if (node->Data().synopsis == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullPictureSynopsis(node, searchKey, vec);
	}
}

vector<Picture> BSTreePicture::searchPartialPictureSynopsis(NodePicture* node, string searchKey)
{
	vector<Picture> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialPictureSynopsis(node, searchKey, vec);
	}
	return(vec);
}

void BSTreePicture::searchPartialPictureSynopsis(NodePicture* node, string searchKey, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchPartialPictureSynopsis(node->Left(), searchKey, vec);
	}
	if (node->Data().synopsis.find(searchKey) != node->Data().synopsis.npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialPictureSynopsis(node->Right(), searchKey, vec);
	}
}

//Receive a vector passed by reference, add all elements of the tree to the vector.
void BSTreePicture::buildVector(NodePicture* node, vector<Picture>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	//Left side recursive.
	if (node->Left() != nullptr)
	{
		buildVector(node->Left(), vec);
	}
	//Add the current node
	vec.push_back(node->Data());
	//Right side recursive
	if (node->Right() != nullptr)
	{
		buildVector(node->Right(), vec);
	}
}

ostream& BSTreePicture::printPictureNode(ostream& out, const Picture& pict)
{
	out << pict.name << ',' << pict.year << ',' << pict.nominations << ','
		<< pict.rating << ',' << pict.duration << ',' << pict.genre1 << ','
		<< pict.genre2 << ',' << pict.release << ',' << pict.metacritic << ','
		<< pict.synopsis << endl;
	return(out);
}


//Sort function goes here.
//Base function: Determine which field to sort from.
//Pass to the appropriate function, return a sorted vector for outputting to file or displaying.
//If the user wants reversed order, use reverse() on the vector.
vector<Picture> BSTreePicture::sortByName(NodePicture* root)
{
	//Since the search tree is already sorted by name, a single call to generateVector is needed.
	vector<Picture> vec;
	buildVector(root, vec);
	return(vec);
}

//Sort by Release Month
vector<Picture> BSTreePicture::sortByRelease(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureRelease);
	//Return the vector
	return(vec);
}
//Rinse and repeat for the other fields.
//Sort by Year
vector<Picture> BSTreePicture::sortByYear(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureYear);
	//Return the vector
	return(vec);
}
//Sort by Duration
vector<Picture> BSTreePicture::sortByDuration(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureDuration);
	//Return the vector
	return(vec);
}
//Sort by Genre1
vector<Picture> BSTreePicture::sortByGenre1(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureGenre1);
	//Return the vector
	return(vec);
}
//Sort by Genre2
vector<Picture> BSTreePicture::sortByGenre2(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureGenre2);
	//Return the vector
	return(vec);
}
//Sort by Nominations
vector<Picture> BSTreePicture::sortByNominations(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureNominations);
	//Return the vector
	return(vec);
}

//Sort by Rating
vector<Picture> BSTreePicture::sortByRating(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureRating);
	//Return the vector
	return(vec);
}

//Sort by Metacritic
vector<Picture> BSTreePicture::sortByMetacritic(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureMetacritic);
	//Return the vector
	return(vec);
}

//Sort by Synopsis
vector<Picture> BSTreePicture::sortBySynopsis(NodePicture* root)
{
	//Generate a vector
	vector<Picture> vec;
	buildVector(root, vec);
	//Sort by the appropriate type
	sort(vec.begin(), vec.end(), comparePictureSynopsis);
	//Return the vector
	return(vec);
}



//Print function goes here.
//Base function: Gather the elements the user wants printed as a series of booleans
//Pass booleans to a private print function to build the output, then return the output to the main program.