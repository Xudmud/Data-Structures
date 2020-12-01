//Gregory Wicklund
//CSCI 2421
//Homework 1
//27 August 2017
//Header file for guess

#include <iostream>
#include <vector>

using namespace std;
class guess
{
	private:
		vector<int> nums;
		vector<int> nums2;
		int size;
		int maxValue;
		bool winner;

	public:
		guess();
		guess(int,int);
		void getRanges();
		void printNums();
		void guessInts();
		bool checkNum(int,int);
		void checkWin();
};