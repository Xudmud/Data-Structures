/* Gregory Wicklund
* Class: CSCI-2421
* Final Project Picture.h file
*/

#ifndef PICTURE_
#define PICTURE_

#include <string>

//Struct for Picture objects. Contains its member variables and a default constructor
//to generate an empty object to either be filled or compared.
struct Picture
{
	std::string name; //this is the key
	int year;
	int nominations;
	double rating;
	int duration;
	std::string genre1;
	std::string genre2;
	std::string release;
	int metacritic;
	std::string synopsis;
	//Source for struct constructor: help from my father
	Picture() { year = 0, nominations = 0, rating = 0, duration = 0, genre1 = "", genre2 = "", release = "", metacritic = 0, synopsis = ""; }
};

//Operators and comparison functions for Picture. Need to be declared
//outside the struct definition to work properly. Source: Help from my father
bool operator ==(const Picture& act1, const Picture& Act2);
bool comparePictureName(const Picture& pic1, const Picture& pic2);
bool comparePictureYear(const Picture& pic1, const Picture& pic2);
bool comparePictureNominations(const Picture& pic1, const Picture& pic2);
bool comparePictureRating(const Picture& pic1, const Picture& pic2);
bool comparePictureDuration(const Picture& pic1, const Picture& pic2);
bool comparePictureGenre1(const Picture& pic1, const Picture& pic2);
bool comparePictureGenre2(const Picture& pic1, const Picture& pic2);
bool comparePictureRelease(const Picture& pic1, const Picture& pic2);
bool comparePictureMetacritic(const Picture& pic1, const Picture& pic2);
bool comparePictureSynopsis(const Picture& pic1, const Picture& pic2);


#endif