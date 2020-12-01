/* Gregory Wicklund
 * Class: CSCI-2421
 * HW 3 Vehicle.cpp file
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Vehicle.h"

//Constructor. Assigns blank values in case no data is read.
Vehicle::Vehicle()
{
	year = 0;
	make = "";
	model = "";
}

Vehicle::Vehicle(std::stringstream& ss)
{
	//Grab inputs from the stringstream.
	ss >> year;
	if (ss.fail())
		std::cout << "Could not read year." << std::endl;
	ss.get(); //filter out the extra \n the stream brought in.
	//Need a solution to this, need to get ss to read up until \n.
	getline(ss, make);
	if (ss.fail())
		std::cout << "Could not read make." << std::endl;
	//ss.get();
	getline(ss, model);
	if (ss.fail())
		std::cout << "Could not read model." << std::endl;
	ss.clear();
}

//Sort first by year, then make, then model.
bool Vehicle::yearComp(const Vehicle& comp, const Vehicle& comp2)
{
	if (comp.year == comp2.year)
	{
		if (comp.make == comp2.make)
		{
			return(comp.model < comp2.model);
		}
		else
		{
			return(comp.make < comp2.make);
		}
	}
	else
	{
		return(comp.year < comp2.year);
	}
}

//Sort first by model, then year, then make.
bool Vehicle::modelComp(const Vehicle& comp, const Vehicle& comp2)
{
	if (comp.model == comp2.model)
	{
		if (comp.year == comp2.year)
		{
			return(comp.make < comp2.make);
		}
		else
		{
			return(comp.year < comp2.year);
		}
	}
	else
	{
		return(comp.model < comp2.model);
	}
}

//Sort first by make, then year, then model
bool Vehicle::makeComp(const Vehicle& comp, const Vehicle& comp2)
{
	if (comp.make == comp2.make)
	{
		if (comp.year == comp2.year)
		{
			return(comp.model < comp2.model);
		}
		else
		{
			return(comp.year < comp2.year);
		}
	}
	else
	{
		return(comp.make < comp2.make);
	}
}

std::ostream& operator<<(std::ostream& cout,Vehicle vehOut)
{
	std::cout << "Year: " << vehOut.year << std::endl;
	std::cout << "Make: " << vehOut.make << std::endl;
	std::cout << "Model: " << vehOut.model << std::endl;
	return(cout);
}

//Function to sort vehicle objects by year.
//Pass by reference?
//Does this need to be a non-member function?
//Code for the actual sorting is in the textbook

//Function to search for specific year


//Function to search for specific make

//Function to search for specific model

//Function to output the result.