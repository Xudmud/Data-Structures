//Gregory Wicklund
//CSCI 2421
//Homework 1
//27 August 2017
//Implementation file for guess.h

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "guess.h"

//Constructor
guess::guess()
{
	//Intentionally empty
}

guess::guess(int sizeIn, int maxValueIn)
{
	size = sizeIn;
	maxValue = maxValueIn;
	for(int i = 0; i < size; i++)
	{
		nums.push_back((std::rand() % maxValue) + 1); //rand() returns a number between 0 and m, add one to offset.
	}

}

//Non-member functions
void startGuess()
{
	//Get size and maxValue
	int size, maxValue;
	cout << "How many numbers? ";
	cin >> size;
	cout << "What's the max value? ";
	cin >> maxValue;

	//Build guess object
	guess answer = guess(size, maxValue);
	//answer.printNums(); //Uncomment to show the vector, to test win conditions.

	//Guess the ints and check for win.
	answer.guessInts();
	answer.checkWin();
	return;
}

string playAgain()
{
	string play;
	int i = 0;
	cout << "Play again? (yes/no) ";
	cin >> play;
	while(play[i])
	{
		//Avoid oddities with Yes/yes/YES, or Y/y
		play[i] = tolower(play[i]);
		i++;
	}
	return play;
}


//Member functions
void guess::printNums()
{
	for(int i = 0; i < nums.size(); i++)
		cout << nums[i] << ' ';
	cout << endl; //For clarity
	return;
}

void guess::guessInts()
{
	cout << "Enter " << nums.size() << " integers between 1 and " << maxValue << ": ";

	for(int i = 0; i < 3; i++)
	{
		//Copy the vector to a temporary variable.
		nums2 = nums;
		
		//Make this a function?
		for(int i = 0; i < nums.size(); i++)
		{
			int value;
			cin >> value;
			bool correct = false;
			for(int j = 0; j < nums2.size() && !correct; j++)
			{
				correct = checkNum(value, j); //Check if the input is correct	
			}
		}
		if(nums2.size() == 0) //size will be 0 if all integers are correctly guessed
		{
			winner = true;
			return;
		}
		else
		{
			cout << "You got " << nums.size() - nums2.size() << " correct. " << endl;
			if(i < 3)
				cout << "Try again: ";
		}
		winner = false;
	}
	return;
}

void guess::checkWin()
{
	if(winner)
	{
		cout << "You win! The integers were ";
		printNums();
	}
	else
	{
		cout << "You lose. The integers were ";
		printNums();
		cout << endl;
	}
	return;
}

bool guess::checkNum(int num,int pos)
{
	if(num == nums2[pos])
		{
			nums2.erase(nums2.begin() + pos);
			return(true);
		}
	return(false); //The guess was not correct.
}