/* Gregory Wicklund
* Class: CSCI-2421
* Final Project ActorFunctions.h file
*/

/*Functions for objects of type Actor that may not need full access to the
 private variables of NodeActor.h or BSTreeActor.h */

#ifndef ACTORFUNCTIONS_
#define ACTORFUNCTIONS_

#include "BSTreeActor.h"
#include "ActorActress.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

//Read functions
void readActorsIn(string fileChoice, BSTreeActor* treeAct);
Actor getNewActorData();

//Other functions
bool actorSanityCheck(BSTreeActor* act);
vector<Actor> searchActor(BSTreeActor* treeAct);
vector<Actor> searchActorResults(vector<Actor> vec);
vector<Actor> searchActorResultsName(vector<Actor> vec);
vector<Actor> searchActorResultsFullName(vector<Actor> vec, string searchTerm);
vector<Actor> searchActorResultsPartialName(vector<Actor> vec, string searchTerm);
vector<Actor> searchActorResultsFilm(vector<Actor> vec);
vector<Actor> searchActorResultsFullFilm(vector<Actor> vec, string searchTerm);
vector<Actor> searchActorResultsPartialFilm(vector<Actor> vec, string searchTerm);
vector<Actor> searchActorResultsAward(vector<Actor> vec);
vector<Actor> searchActorResultsFullAward(vector<Actor> vec, string searchTerm);
vector<Actor> searchActorResultsPartialAward(vector<Actor> vec, string searchTerm);
vector<Actor> searchActorResultsYear(vector<Actor> vec);
vector<Actor> searchActorResultsFullYear(vector<Actor> vec, int searchTerm);
vector<Actor> searchActorResultsPartialYear(vector<Actor> vec, string searchTerm);
vector<Actor> searchActorResultsWinLose(vector<Actor> vec);
vector<Actor> searchActorResultsWin(vector<Actor> vec);
vector<Actor> searchActorResultsLose(vector<Actor> vec);
vector<Actor> searchActorName(BSTreeActor* act);
vector<Actor> searchFilmTitle(BSTreeActor* act);
vector<Actor> searchYear(BSTreeActor* act);
vector<Actor> searchAward(BSTreeActor* act);
vector<Actor> searchWinLose(BSTreeActor* act);
vector<Actor> emptyActorData();
Actor changeActorFields(Actor act);
void addActorNode(BSTreeActor* act);
void deleteActorNode(BSTreeActor* act);
void deleteSelectedNodes(BSTreeActor* act, const vector<Actor>& vec);
bool defaultActor(Actor act);
void modifyActorNode(BSTreeActor* tree, Actor act);

//Sort functions
vector<Actor> sortActors(BSTreeActor* treeAct);
vector<Actor> sortActors(const vector<Actor>& vec);
void modifyActorData(BSTreeActor* treeAct);


//Search result sort functions
vector<Actor> sortByName(vector<Actor> vec);
vector<Actor> sortByFilm(vector<Actor> vec);
vector<Actor> sortByYear(vector<Actor> vec);
vector<Actor> sortByAward(vector<Actor> vec);
vector<Actor> sortByWinner(vector<Actor> vec);

//Print functions
void printActorsToFile(BSTreeActor* tree);
void printActorsToFile(vector<Actor> vec);
void displayCurrentChoices(const bool fieldsToPrint[5]);

void printActor(const Actor& act);
void printActor(ofstream& fout, const bool fieldsToPrint[5]);
void printActor(ofstream& fout, Actor act, const bool fieldsToPrint[5]);
void printActorHead(ostream& out);

#endif