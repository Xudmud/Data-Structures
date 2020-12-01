/* Gregory Wicklund
* Class: CSCI-2421
* HW 7 Bank.cpp file
*/

#include <queue>
#include <fstream>
#include <iostream>
#include "Bank.h"

using namespace bankqueue;
using namespace std;

Bank::Bank() //Constructor
{
	currentTime = 0;
	waitTime = 0;
	customerCount = 0;
}

void Bank::grabNext()
{
	patron temp = priCue.top();
	//Determine wait time (if any)
	if (priCue.top().arriveTime < currentTime)
	{
		waitTime += (currentTime - priCue.top().arriveTime);
	}
	else
	{
		//current time would be whenever this event is processed.
		currentTime = priCue.top().arriveTime;
	}

	//Called event
	temp.calledTime = currentTime;
	//Departure event
	temp.departTime = temp.calledTime + temp.tenderTime;
	currentTime += temp.tenderTime;
	cue.push(temp);
	priCue.pop();
	//}
}

void Bank::readPatrons(std::istream& in)
{
	while (!in.eof())
	{
		patron temp;
		//Arrival event
		in >> temp.arriveTime;
		if (in.fail())
			return; //avoid getting an incorrect customer count.
		in >> temp.tenderTime;
		if (in.fail())
			return;
		priCue.push(temp);
		customerCount++;
	}
}

void Bank::process()
{
	while (!priCue.empty())
	{
		grabNext();
	}
	//While loop to generate the event list.
	//Interestingly, ties seem to be awarded to departures.
	while (!cue.empty())
	{
		//For loop: once for arrival, once for being seen, once for departure.
		for (int i = 0; i < 2; i++)
		{
			events temp;
			switch (i)
			{
			case 0:
				temp.type = 'A';
				temp.eventTime = cue.front().arriveTime;
				break;
			case 1:
				temp.type = 'D';
				temp.eventTime = cue.front().departTime;
				break;
			default:
				//This code should never run, but using as a safeguard
				cout << "Undefined Error (0x1)" << endl;
				exit(1);
				break;
			} //Switch
			eventList.emplace(temp);
		} //For
		//Take the item off the queue.
		cue.pop();
	} //While
	
}

void Bank::printResults()
{
	char arrivals = 'A';
	char departures = 'A';
	while (!eventList.empty())
	{
		switch (eventList.top().type)
		{
		case 'A':
			cout << "Customer " << arrivals++ << " arrived at time " << eventList.top().eventTime << endl;
			eventList.pop();
			break;
		case 'D':
			cout << "Customer " << departures++ << " departed at time " << eventList.top().eventTime << endl;
			eventList.pop();
			break;
		default:
			cout << "Undefined error (0x2)";
			exit(2);
			break;
		}
	}
	cout << "-------------------------------------------------" << endl;
	cout << "Total waiting time: " << waitTime << endl;
	cout << "Total people processed: " << customerCount << endl;
	cout << "Average wait time: " << (double)waitTime / (double)customerCount << endl;
}