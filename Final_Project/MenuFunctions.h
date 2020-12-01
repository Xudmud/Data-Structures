/* Gregory Wicklund
* Class: CSCI-2421
* Final Project MenuFunctions.h file
*/

#ifndef MENUFUNCTIONS_
#define MENUFUNCTIONS_

/*#include "BSTreeActor.h"
#include "NodeActor.h"
#include "ActorFunctions.h"
#include <vector>*/

#include <string>
void mainMenu();

//Menu choice functions
int displayMainOptions();
int displayDataTypeOptions();
int displayActorSearchOptions();
int displayActorWinLoseOptions();
int displayPartialCompleteOptions();
int displaySearchWithinResultsOptions();
int displayActorSortOptions();
int displayActorOutputOptions();
int displayProceedConfirmation();
int displayModifyFieldOptions();
int displayModifyPictureOptions();
int displayActorPrintOptions();
int displayPicturePrintOptions();
int displayDataSourceOptions();
int displayMonthOptions();
int displayPictureSortOptions();
int displayPictureSearchOptions();
bool fileExists(std::string filename);

//Functions for getting search and filename
std::string getFileNameChoice();
std::string getStringSearch();
std::string getYearStringSearch();
std::string getDoubleStringSearch();
void fileExistsWarning();

#endif