/* Gregory Wicklund
* Class: CSCI-2421
* Final Project ActorActress.h file
*/

#ifndef ACTORACTRESS_
#define ACTORACTRESS_

#include <string>

//This struct can handle both actor and nomination, since they have the same fields.
//Actor struct, contains its member functions, and a default constructor to generate
//an empty set of data.
//The only real difference between a struct and a class is if its members are public or
//private by default. Source: https://stackoverflow.com/questions/1127396/struct-constructor-in-c
struct Actor
{
	int year;
	std::string award;
	bool winner;
	std::string name; //this is the key
	std::string film;
	Actor() { year = 0, award = "", winner = 0, name = "", film = ""; }
};

//Operators for Actor. Need to be declared outside the struct
//definition to work properly. Source: Help from my father
bool operator ==(const Actor& act1, const Actor& Act2);
bool compareName(const Actor& act1, const Actor& act2);
bool compareFilm(const Actor& act1, const Actor& act2);
bool compareYear(const Actor& act1, const Actor& act2);
bool compareAward(const Actor& act1, const Actor& act2);
bool compareWinner(const Actor& act1, const Actor& act2);

#endif