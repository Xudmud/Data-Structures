/* Gregory Wicklund
* CSCI 2421
* Final Project: BSTreeActor.cpp file
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



#include "BSTreeActor.h"
#include "ActorFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

// Constructor
BSTreeActor::BSTreeActor() {
	root = new NodeActor;
}

// Destructor
BSTreeActor::~BSTreeActor() {
	if (root != nullptr)
		freeNode(root);
}



// Free the node
void BSTreeActor::freeNode(NodeActor* leaf)
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
void BSTreeActor::addNode(string key, Actor act)
{
	if (defaultActor(act)) //Actor object is empty, no need to add. Do nothing and return.
		return;
	//Check if root is nullptr, if so set the root and add the key.
	if (root == nullptr)
	{
		//Create a new node, add the key. Left, right, and parent get set to nullptr by the constructor.
		root = new NodeActor;
		root->setKey(key);
		root->setData(act);
		//Increment the count
	}
	else if (root->Key() == "-1") //Might need a different test value
	{
		root->setKey(key);
		root->setData(act);
		//Left(), Right(), and Parent() are set to nullptr by the constructor.
		//Increment the count
	}
	//left and right get set to nullptr already by the constructor.

	//Start navigating the tree to add the node.
	else if (key < root->Key())
	{
		//Check if left node is null
		if (root->Left() == nullptr)
			//Add a new node to the left.
		{
			NodeActor* tempnode = new NodeActor;
			tempnode->setKey(key);
			tempnode->setData(act);
			//left and right get set to nullptr, need to set parent.
			//In this case, it's root.
			tempnode->setParent(root);
			//Set root's left to the new node.
			root->setLeft(tempnode);
			//successfully added a node, increment the count.
		}
		else
		{
			//Call the recursive function, which will treat root's left as "root"
			addNode(key, root->Left(), act);
		}
	}

	else //key is greater than or equal, go right.
	{
		//Check if right node is null.
		if (root->Right() == nullptr)
		{
			NodeActor* tempnode = new NodeActor;
			tempnode->setKey(key);
			tempnode->setData(act);
			tempnode->setParent(root);
			root->setRight(tempnode);
		}
		else
		{
			addNode(key, root->Right(), act);
		}
	}
	addCount();
	//Student must fill in
	//Base Case: No elements. Add the root and set the key
	//Otherwise use recursive (private) addNode

}

// Add a node (private)
void BSTreeActor::addNode(string key, NodeActor* leaf, Actor act)
{
	//Check if the key is less than the current leaf.
	if (key < leaf->Key())
	{
		//If so, key is less and goes on the left.
		//Check if the next leaf on left is null.
		if (leaf->Left() == nullptr)
		{
			//If so, crate a new node, add the information.
			NodeActor* tempnode = new NodeActor;
			//tempnode's key is the passed key value.
			tempnode->setKey(key);
			tempnode->setData(act);
			//tempnode's parent should be the leaf.
			tempnode->setParent(leaf);
			//As the key's value is less, assign the node to the left.
			leaf->setLeft(tempnode);
			//The right node is already set to nullptr by the constructor
		} //if
		  //Otherwise, call addNode(key, leaf->Left()) to traverse one leaf down.
		else
		{
			addNode(key, leaf->Left(), act);
		} //else
	} //if
	  //Else, the key must be greater than or equal to the leaf's key. Check if the leaf's right branch is null.
	else
	{
		if (leaf->Right() == nullptr)
		{
			//If so, set the key's right branch to the key, and set the parent node. Then attach the node to the right of the leaf.
			NodeActor* tempnode = new NodeActor;
			tempnode->setKey(key);
			tempnode->setData(act);
			tempnode->setParent(leaf);
			leaf->setRight(tempnode);
		} //if
		else
		{
			//Otherwise, call addNode(key, leaf->Right()) to traverse one leaf down
			addNode(key, leaf->Right(), act);
		} //else
	} //if

	  //Student must fill in
	  //Don't forget to set your key, Parent, then left or right
	  //Based on the case you use you will addNode recursively to the left or right

}

NodeActor* BSTreeActor::findNode(string key)
{
	return findNode(key, root);
}

// Find a node
NodeActor* BSTreeActor::findNode(string key, NodeActor* node)
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

void BSTreeActor::printInorder()
{
	printInorder(root);
}

void BSTreeActor::printInorder(NodeActor* aNode)
{
	//Code taken from in-class BSTreeint.cpp example.
	/*******************************************/
	if (aNode != nullptr)
	{
		if (aNode->Left() != nullptr)
			printInorder(aNode->Left());
		if (!defaultActor(aNode->Data()))
			//Need a separate function to handle the print because of c++ left-to-right rule.
			printActorNode(cout, aNode->Data());
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

void BSTreeActor::printFileInOrder(ostream& out)
{
	printFileInOrder(out, root);
}

void BSTreeActor::printFileInOrder(ostream& out, NodeActor* aNode)
{
	if (aNode != nullptr)
	{
		if (aNode->Left() != nullptr)
			printFileInOrder(out, aNode->Left());
		if (!defaultActor(aNode->Data()))
			printActorNode(out, aNode->Data());
		if (aNode->Right() != nullptr)
			printFileInOrder(out, aNode->Right());
	}
}

void BSTreeActor::deleteNode(string key)
{
	{
		if (deleteNode(Root(), key) == nullptr)
		{
			setRoot(nullptr);
		}
	}
}

//deleteNode (Private)
NodeActor* BSTreeActor::deleteNode(NodeActor* root, string key)
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
			removeCount();
			// Case 2: one child
		}
		else if (root->Left() == nullptr) {
			/*********Changed this portion***************/
			//Set a temp node equal to root's right
			NodeActor* temp = root->Right();
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
			removeCount();
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
			NodeActor* temp = root->Left();
			root->setKey(temp->Key());
			root->setData(temp->Data());
			root->setLeft(temp->Left());
			root->setRight(temp->Right());
			delete temp;
			removeCount();
			/*******************************************/
			/*Original Code
			* Node *temp = root;
			* root = root->Left();
			* delete temp;
			*/
		}
		else {
			NodeActor *temp = min(root->Right());
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
NodeActor* BSTreeActor::min(NodeActor* node)
{
	NodeActor* tempNode = node;
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
NodeActor* BSTreeActor::max(NodeActor* node)
{
	NodeActor * tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Right())
		tempNode = max(node->Right());
	else
		tempNode = node;

	return tempNode;
}

//Added functions
Actor BSTreeActor::readInput(ifstream& fin)
{
	Actor temp;
	string str;

	//Get year
	getline(fin, str, ',');
	if (str != "" && str.find_first_not_of("0123456789") == str.npos)
		temp.year = stoi(str);
	else
		temp.year = 0;

	//Get award
	//Check if string is in quotes
	if (fin.peek() == '\"')
	{
		fin.ignore(); //Clear the quote out
		str = "";
		//Read in the entry. Since some may have quotes in the middle of them, keep going until the next comma after a " is reached.
		//Limiation: This assumes that all times a comma follows a quote are when it's between fields.  Using an alternate delimiter,
		//such as | could alleviate this.
		do
		{
			string temp;
			getline(fin, temp, '\"');
			str += temp;
			str += "\""; //put the quote back in that getline would strip
		} while (fin.peek() != ',');
		str.pop_back(); //strip out the final character, which would be a quote.
		fin.ignore(); //Clear the comma out
	}
	else
		getline(fin, str, ',');
	temp.award = str;
	getline(fin, str, ',');

	//For winner, this assumes false unless the csv file specifies otherwise.
	if (str != "" && str.find_first_not_of("0123456789") == str.npos)
		temp.winner = (bool)(stoi(str));
	else
		temp.winner = false;

	//Get name, checking for quotes
	if (fin.peek() == '\"')
	{
		fin.ignore();
		do
		{
			string temp;
			getline(fin, temp, '\"');
			str += (temp);
			str += "\"";
		} while (fin.peek() != ',');
		str.pop_back();
		fin.ignore();
	}
	else
		getline(fin, str, ',');
	temp.name = str;

	//Get film. Again, check for quotes.
	if (fin.peek() == '\"')
	{
		fin.ignore();
		getline(fin, str);
		str.pop_back(); //Delete the last character of the string, which should be the second ".
	}
	else
	{
		getline(fin, str);
		//Used trial-and-error driver to figure out reading the end.
		if (str.size() != 0)
			//Need these separate to avoid a potential -1 as an unsigned int
			if (str[str.size() - 1] == ',')
				str.pop_back();
	}
	temp.film = str;


	//Return the Actor object, which is used for the data of the NodeActor object.
	return(temp);
}

void BSTreeActor::printActorCount()
{
	cout << "There are currently " << count << " elements in the database.\n" << endl;
}

//Search functions
vector<Actor> BSTreeActor::searchFullActorName(NodeActor* node, string searchKey)
{
	//Since the actor's name is the key, the search can just use key.
	vector<Actor> vec;
	if (node == nullptr) //Base case, in case the tree is empty.
	{
		return(vec);
	}
	else
	{
		//Call the recursive search function to search the tree and fill the vector.
		searchFullActorName(node, searchKey, vec);
	}
	return(vec);
}

void BSTreeActor::searchFullActorName(NodeActor* node, string searchKey, vector<Actor>& vec)
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
		searchFullActorName(node->Right(), searchKey, vec);
	}
	else if (searchKey < node->Key())
	{
		if (node->Left() == nullptr)
		{
			return;
		}
		else
		{
			searchFullActorName(node->Left(), searchKey, vec);
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
			searchFullActorName(node->Right(), searchKey, vec);
		}
	}
}

vector<Actor> BSTreeActor::searchPartialActorName(NodeActor* node, string searchKey)
{
	//Since the actor's name is the key, the search can just use keys.
	//Partial search needs to search every node, since partial matches could be to the left or right.
	//The way the search is coded, it will search for any instance of the search term in the approrpiate field.
	//(e.g. a search for "Harry" cound find "Harry Dresden", or "Patrick Harry" as a match).
	//Code adapted from the printInOrder() function.
	vector<Actor> vec;
	if (node == nullptr) //Base case, in case the tree is empty.
	{
		return(vec);
	}
	else
	{
		searchPartialActorName(node, searchKey, vec);
	}
	return(vec);
}

void BSTreeActor::searchPartialActorName(NodeActor* node, string searchKey, vector<Actor>& vec)
{
	//Need to search the entire tree, since some results could fall on either side of any given node.
	//Search left (if applicable)
	if (node->Left() != nullptr)
	{
		searchPartialActorName(node->Left(), searchKey, vec);
	}
	//Search current

	//Check if node's partial key matches the partial search.
	//Source: Source for partial compare: http://www.cplusplus.com/reference/string/string/find/
	if (node->Key().find(searchKey) != node->Key().npos)
	{
		//Add the Actor object if it is.
		vec.push_back(node->Data());
	}
	//Search right
	if (node->Right() != nullptr)
	{
		searchPartialActorName(node->Right(), searchKey, vec);
	}
	//Vector was passed by reference, no need to return it here.
}

//Searches for other fields are virtually identical as Name, except
//instead of the node's key I need to compare the appropriate variable T
//in them (node->Data().T).  Also, for both complete and partial search
//they need to use an inorder traversal to ensure every node gets searched.
vector<Actor> BSTreeActor::searchFullFilm(NodeActor* node, string searchKey)
{
	//Similar to searchFullActorName, just use the appropriate field.
	vector<Actor> vec;
	if(node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullActorName(node, searchKey, vec);
	}
	return(vec);
}

void BSTreeActor::searchFullFilm(NodeActor* node, string searchKey, vector<Actor>& vec)
{
	//Since the tree isn't sorted by film title, we'll need to search the entire tree.
	if (node == nullptr)
	{
		return;
	}
	//Search to the left, if appropriate.
	if (node->Left() != nullptr)
	{
		searchFullFilm(node->Left(), searchKey, vec);
	}
	if (node->Data().film == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullFilm(node->Right(), searchKey, vec);
	}
}

vector<Actor> BSTreeActor::searchPartialFilm(NodeActor* node, string searchKey)
{
	vector<Actor> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialFilm(node, searchKey, vec);
	}
	return(vec);
}

void BSTreeActor::searchPartialFilm(NodeActor* node, string searchKey, vector<Actor>& vec)
{
	if (node->Left() != nullptr)
	{
		searchPartialFilm(node->Left(), searchKey, vec);
	}
	//Source for partial compare: http://www.cplusplus.com/reference/string/string/find/
	if (node->Data().film.find(searchKey) != node->Data().film.npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialActorName(node->Right(), searchKey, vec);
	}
}

//Change for year
vector<Actor> BSTreeActor::searchFullYear(NodeActor* node, int searchKey)
{
	//Similar to searchFullActorName, just use the appropriate field.
	vector<Actor> vec;
	if(node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullYear(node, searchKey, vec);
	}
	return(vec);
}

void BSTreeActor::searchFullYear(NodeActor* node, int searchKey, vector<Actor>& vec)
{
	//Since the tree isn't sorted by film title, we'll need to check the entire tree.
	//Base case: current node is nullptr.
	if (node == nullptr)
	{
		return;
	}
	//Check the left, if appropriate.
	if (node->Left() != nullptr)
	{
		searchFullYear(node->Left(), searchKey, vec);
	}
	//Check the current node
	if (node->Data().year == searchKey)
	{
		vec.push_back(node->Data());
	}
	//Check the current node to the right.
	if (node->Right() != nullptr)
	{
		searchFullYear(node->Right(), searchKey, vec);
	}
}

vector<Actor> BSTreeActor::searchPartialYear(NodeActor* node, string searchKey)
{
	vector<Actor> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialYear(node, searchKey, vec);
	}
	return(vec);
}

void BSTreeActor::searchPartialYear(NodeActor* node, string searchKey, vector<Actor>& vec)
{
	//Create temporary string to handle film year.
	if (node->Left() != nullptr)
	{
		searchPartialFilm(node->Left(), searchKey, vec);
	}
	//Source for to_string function call:
	//http://www.cplusplus.com/reference/string/to_string/
	if (to_string(node->Data().year).find(searchKey) != to_string(node->Data().year).npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialActorName(node->Right(), searchKey, vec);
	}
}

//Change for award name
vector<Actor> BSTreeActor::searchFullAward(NodeActor* node, string searchKey)
{
	//Similar to searchFullActorName, just use the appropriate field.
	vector<Actor> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchFullAward(node, searchKey, vec);
	}
	return(vec);
}

void BSTreeActor::searchFullAward(NodeActor* node, string searchKey, vector<Actor>& vec)
{
	//Since the tree isn't sorted by film title, we'll need to search the entire tree.
	if (node == nullptr)
	{
		return;
	}
	//Search to the left, if appropriate.
	if (node->Left() != nullptr)
	{
		searchFullAward(node->Left(), searchKey, vec);
	}
	if (node->Data().award == searchKey)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchFullAward(node->Right(), searchKey, vec);
	}
}

//This is where searching the entire string for a given term comes into play,
//if the user, for example, wanted all "Best Actress" and "Best Supporting Actress"
//awards, they could get that with just using the search term "Actress"
vector<Actor> BSTreeActor::searchPartialAward(NodeActor* node, string searchKey)
{
	vector<Actor> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		searchPartialFilm(node, searchKey, vec);
	}
	return(vec);
}

void BSTreeActor::searchPartialAward(NodeActor* node, string searchKey, vector<Actor>& vec)
{
	if (node->Left() != nullptr)
	{
		searchPartialAward(node->Left(), searchKey, vec);
	}
	if (node->Data().award.find(searchKey) !=  node->Data().award.npos)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchPartialAward(node->Right(), searchKey, vec);
	}
}

vector<Actor> BSTreeActor::searchWinLose(NodeActor* node, bool win)
{
	//For this one, determine if the user wants to search for winner or loser, and call that appropriate function.
	vector<Actor> vec;
	if (node == nullptr)
	{
		return(vec);
	}
	else
	{
		if (win)
		{
			searchActorWin(node, vec);
		}
		else
		{
			searchActorLose(node, vec);
		}
	}
	return(vec);
}

void BSTreeActor::searchActorWin(NodeActor* node, vector<Actor>& vec)
{
	//Since the tree isn't sorted by film title, we'll need to search the entire tree.
	if (node == nullptr)
	{
		return;
	}
	//Search to the left, if appropriate.
	if (node->Left() != nullptr)
	{
		searchActorWin(node->Left(), vec);
	}
	if (node->Data().winner)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchActorWin(node->Right(), vec);
	}
}

void BSTreeActor::searchActorLose(NodeActor* node, vector<Actor>& vec)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->Left() != nullptr)
	{
		searchActorLose(node->Left(), vec);
	}
	if (!node->Data().winner)
	{
		vec.push_back(node->Data());
	}
	if (node->Right() != nullptr)
	{
		searchActorLose(node->Right(), vec);
	}
}

//Receive a vector passed by reference, add all elements of the tree to the vector.
//Built based on the printInOrder() function, separately because there are times when
//the program needs just the vector without printing the tree.
void BSTreeActor::buildVector(NodeActor* node, vector<Actor>& vec)
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
	//Add the current node.
	vec.push_back(node->Data());
	//Right side recursive
	if (node->Right() != nullptr)
	{
		buildVector(node->Right(), vec);
	}
}

//Included for the printInOrder() portion of the assignment, but a different
//function is used for printing.
ostream& BSTreeActor::printActorNode(ostream& out, const Actor& act)
{
	out << act.year << ',' << act.award << ',';
	if (act.winner)
		out << "1";
	else
		out << "0";
	out << ',' << act.name << ',' << act.film << endl;
	return(out);
}




//Sort function goes here.
//Base function: Determine which field to sort from.
//Pass to the appropriate function, return a sorted vector for outputting to file or displaying.
//If the user wants reversed order, use reverse() on the vector.
vector<Actor> BSTreeActor::sortByName(NodeActor* root)
{
	//Since the search tree is already sorted by name, a single call to generateVector is needed.
	vector<Actor> vec;
	buildVector(root, vec);
	return(vec);
}

vector<Actor> BSTreeActor::sortByFilm(NodeActor* root)
{
	//Start by generating a vector.
	vector<Actor> vec;
	buildVector(root, vec);
	//Sort the vector
	sort(vec.begin(), vec.end(), compareFilm);
	//Return the sorted vector
	return(vec);
}

vector<Actor> BSTreeActor::sortByYear(NodeActor* root)
{
	vector<Actor> vec;
	buildVector(root, vec);
	sort(vec.begin(), vec.end(), compareYear);
	return(vec);
}

vector<Actor> BSTreeActor::sortByAward(NodeActor* root)
{
	vector<Actor> vec;
	buildVector(root, vec);
	sort(vec.begin(), vec.end(), compareAward);
	return(vec);
}

vector<Actor> BSTreeActor::sortByWinner(NodeActor* root)
{
	vector<Actor> vec;
	buildVector(root, vec);
	sort(vec.begin(), vec.end(), compareWinner);
	return(vec);
}

/*This can be used for a sort-in-reverse function, replacing T with whatever field is needed.
vector<Actor> BSTreeActor::sortByTDescending(NodeActor* root)
{
	vector<Actor> vec;
	buildVector(root, vec);
	sort(vec.begin(), vec.end(), compareTDescending);
}
*/