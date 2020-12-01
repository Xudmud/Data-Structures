/* Gregory Wicklund
 * Class: CSCI-2421
 * HW 3 Vehicle.h file
 */

#ifndef VEHICLE
#define VEHICLE

#include <iostream>
#include <vector>
#include <string>
#include <sstream>


class Vehicle
{
	//Recursive is a friend.
	friend class Recursive;
	private:
		int year;
		std::string model;
		std::string make;

	public:
		Vehicle(); //Default
		Vehicle(std::stringstream&);
//		Vehicle(Vehicle& old);

		//Sort functions
		static bool yearComp(const Vehicle&,const Vehicle&);
		static bool modelComp(const Vehicle&, const Vehicle&);
		static bool makeComp(const Vehicle&, const Vehicle&);

		friend std::ostream& operator <<(std::ostream&, Vehicle);
};

#endif