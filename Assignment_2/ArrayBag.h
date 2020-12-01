/* Gregory Wicklund
 * Class: CSCI-2421
 * HW 2 ArrayBag.h file
 */

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2016 __Pearson Education__. All rights reserved.
//Modified by TAA to remove templates and Inheritance

/** ADT bag: Array-based implementation.
 @file ArrayBag.h */


#ifndef BAG_
#define BAG_

#include <vector>
#include <sstream>

typedef int ItemType; //Defines ItemType as an int?
class ArrayBag
{
private:
	static const int DEFAULT_BAG_SIZE = 100;
	ItemType items[DEFAULT_BAG_SIZE]; // array of bag items
   int itemCount;                    // current count of bag items 
   int maxItems;                     // max capacity of the bag
   
   // Returns either the index of the element in the array items that
   // contains the given target or -1, if the array does not contain 
   // the target.
   int getIndexOf(const ItemType& target) const;   

public:
	ArrayBag();
	int getCurrentSize() const;
	bool addItems(std::stringstream&, ArrayBag&);
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
    std::vector<ItemType> toVector() const;
    friend ArrayBag operator+(ArrayBag&,ArrayBag&);
    friend ArrayBag operator-(ArrayBag&,ArrayBag&);
    void printBag();
};  // end Bag


#endif
