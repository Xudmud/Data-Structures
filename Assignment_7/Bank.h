/* Gregory Wicklund
* Class: CSCI-2421
* HW 7 Bank.h file
*/

#ifndef BANK_H
#define BANK_H

#include <queue>
#include <iostream>
#include <vector>

namespace bankqueue
{
	struct patron
	{
		int arriveTime;
		int tenderTime;
		int calledTime; //gets filled in later
		int departTime; //gets filled in later
	};

	struct events
	{
		char type;
		int eventTime;
	};

	struct TimeCompare
	{
		bool operator()(const patron& left, const patron& right)
		{
			return(left.arriveTime > right.arriveTime);
		}
	};

	struct eventCompare
	{
		bool operator()(const events& event1, const events& event2)
		{
			return(event1.eventTime > event2.eventTime);
		}
	};

	class Bank
	{
	private:
		std::priority_queue<patron, std::vector<patron>, TimeCompare> priCue;
		std::queue<patron> cue;
		std::priority_queue<events, std::vector<events>, eventCompare> eventList;
		int currentTime;
		int waitTime;
		int customerCount;

	public:
		Bank();
		//void addEntry();
		void readPatrons(std::istream& in);
		void process();
		void grabNext();
		void printResults();
		//void readEvents();
		

		//void calcAverage();


	};
}

#endif