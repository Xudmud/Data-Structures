/* Gregory Wicklund
 * Class: CSCI-2421
 * HW 2 ArrayBag.cpp file
 * Corrected ArrayBag constructor, added addItems(), printBag(), and
 * overloaded + and - operators.
 */

//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2016 __Pearson Education__. All rights reserved.
//Modified by TAA to remove Template and Inheritance

/** @file ArrayBag.cpp */

#include "ArrayBag.h"
#include <iostream>
#include <sstream>


ArrayBag::ArrayBag() : itemCount(0), maxItems(DEFAULT_BAG_SIZE)
{
}  // end default constructor


int ArrayBag::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

//Function for adding items. Validates each element is actually an
//int before adding.
bool ArrayBag::addItems(std::stringstream& ss, ArrayBag& bag)
{
   int k;
   while(!ss.eof())
   {
      ss >> k;
      if(ss.fail())
      {
         std::cout << "Invalid input in file.\n";
         ss.clear();
         return(false);
      }
      bag.add(k);
   }
   return(true);
}

bool ArrayBag::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty


bool ArrayBag::add(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (hasRoomToAdd)
	{
		items[itemCount] = newEntry;
		itemCount++;
	}  // end if
    
	return hasRoomToAdd;
}  // end add


bool ArrayBag::remove(const ItemType& anEntry)
{
   int locatedIndex = getIndexOf(anEntry);
	bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
	if (canRemoveItem)
	{
		itemCount--;
		items[locatedIndex] = items[itemCount];
	}  // end if
    
	return canRemoveItem;
}  // end remove


void ArrayBag::clear()
{
	itemCount = 0;
}  // end clear


int ArrayBag::getFrequencyOf(const ItemType& anEntry) const
{
   int frequency = 0;
   int searchIndex = 0;
   while (searchIndex < itemCount)
   {
      if (items[searchIndex] == anEntry)
      {
         frequency++;
      }  // end if
      
      searchIndex++;
   }  // end while
   
   return frequency;
}  // end getFrequencyOf


bool ArrayBag::contains(const ItemType& anEntry) const
{
	return getIndexOf(anEntry) > -1;
}  // end contains



std::vector<ItemType> ArrayBag::toVector() const
{
    std::vector<ItemType> ArrayBagContents;
	for (int i = 0; i < itemCount; i++)
                ArrayBagContents.push_back(items[i]);
   return ArrayBagContents;
}  // end toVector

// private

int ArrayBag::getIndexOf(const ItemType& target) const
{
	bool found = false;
   int result = -1;
   int searchIndex = 0;
   // if the ArrayBag is empty, itemCount is zero, so loop is skipped
   while (!found && (searchIndex < itemCount))
   {
      if (items[searchIndex] == target)
      {
         found = true;
         result = searchIndex;
      } 
      else
      {
         searchIndex++;
      }  // end if
   }  // end while
   
   return result;
}  // end getIndexOf

//Print function
void ArrayBag::printBag()
{
   //Assign to a vector to print the array.
   std::vector<int> vec = this->toVector();
   for(int i = 0; i < vec.size(); i++)
   {
      std::cout << vec[i] << ' ';
   }
   std::cout << "\n\n";
}

//Overloaded Operators
ArrayBag operator +(ArrayBag& bagLeft,ArrayBag& bagRight)
{
   
   ArrayBag temp;
   //Add each unique element to the temp ArrayBag.
   for(int i = 0; i < bagLeft.getCurrentSize(); i++)
   {
      if(!temp.contains(bagLeft.items[i]))
      {
         temp.add(bagLeft.items[i]);
      }
   }
   //Doing this a second time, it could be put in a function.
   for(int i = 0; i < bagRight.getCurrentSize(); i++)
   {
      if(!temp.contains(bagRight.items[i]))
      {
         temp.add(bagRight.items[i]);
      }
   }
   return(temp);
}

ArrayBag operator -(ArrayBag& bagLeft,ArrayBag& bagRight)
{
   ArrayBag temp;
   //Start the same as the + operator
   for(int i = 0; i < bagLeft.getCurrentSize(); i++)
   {
      if(!temp.contains(bagLeft.items[i]))
      {
         temp.add(bagLeft.items[i]);
      }
   }
   //Remove each instance of an object in the second ArrayBag.
   for(int i = 0; i < bagRight.getCurrentSize(); i++)
   {
      if(bagLeft.contains(bagRight.items[i]))
      { 
         bool yes;
         yes = temp.remove(bagRight.items[i]);
      }
   }
   return(temp);
}