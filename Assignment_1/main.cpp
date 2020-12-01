#include "guess.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
//Declare startGUess function.
void startGuess();
string playAgain();

int main(int argc, char* argv[])
{
	//Initialize seed
	srand(time(NULL));

	//initialize string for end of program.
	string again;
	
	//run guess program until user is done.
	do
	{
		startGuess();
		again = playAgain();
	} while(again == "yes" || again == "y");  //Runs again on "yes" or "y", exits on anything else.
	
	return 0;  //Indicates the program exited successfully, also mitigates a stack smashing error
}

