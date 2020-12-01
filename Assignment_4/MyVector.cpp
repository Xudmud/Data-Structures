/* Gregory Wicklund
 * Class: CSCI-2421
 * HW 4 MyVector.cpp file
 * Analysis for operator [], pop_back(), push_back(), and search are
 * in the analysis.txt file.
 */

#include "MyVector.h"
#include <iostream>

//Define the namespace again? According to the tips, yes.
namespace HW4
{
	MyVector::MyVector()
	{
		//Default constructor, intentionally empty.
	}

	T MyVector::operator [] (int index)
	{
		if (index >= vsize) //trying to access entries outside the array
		{
			std::cout << "Tried to access outside the array. Aborting." << std::endl;
			exit(1);
		}
		return(vec[index]); //Returning the current position.
	}

	void MyVector::pop_back()
	{
		//Do nothing if the size is already 0. Could set a try/catch for exception handling.
		//Curious what situation would involve using pop_back on an empty vector...
		if (empty())
		{
			std::cout << "Vector is empty, nothing to remove.\n\n";
			return;
		}
		else
		{
			//All that really is needed here is decrementing vsize.
			//The next push_back() will overwrite the old pointer.
			vsize--; //Decrement the size by one.
		}
	}

	void MyVector::push_back(T value)
	{
		//vsize happens to be 
		T* vec2 = vec;
		vec = new T[vsize + 1];
		//Copy the array to a new array of size vsize+1

		for (int i = 0; i < vsize; i++)
		{
			vec[i] = vec2[i];
		}

		//We're done with the copy array, so free the memory.
		delete[] vec2;

		//Add the new element to the end.
		vec[vsize] = value;
		vsize++;
	}

	int MyVector::size()
	{
		//Return whatever the current size is.
		return(vsize);
	}

	bool MyVector::empty()
	{
		//vsize should be 0 if the vector is empty.
		//A simple boolean check on vsize should suffice
		return(vsize == 0);
	}

	int MyVector::search(T Value)
	{
		//Big-O would be the size of the array we're working with.
		//Using sort would add to the computation time, plus modify the contents of the array.
		for (int i = 0; i < size(); i++)
		{
			if (Value == vec[i])
				return(i);
		}
		return(-1);
	}
}