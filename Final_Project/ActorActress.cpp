/* Gregory Wicklund
* Class: CSCI-2421
* Final Project ActorActress.cpp file
*/

#include "ActorActress.h"

//Equality operator
bool operator ==(const Actor& act1, const Actor& act2)
{
	if (act1.name == act2.name)
	{
		if (act1.film == act2.film)
		{
			if (act1.award == act2.award)
			{
				if (act1.winner == act2.winner)
				{
					if (act1.year == act2.year)
					{
						return(true);
					}
				}
			}
		}
	}
	return(false);
}


//Compare functions.
bool compareName(const Actor& act1, const Actor& act2)
{
	return(act1.name < act2.name);
}

bool compareFilm(const Actor& act1, const Actor& act2)
{
	return(act1.film < act2.film);
}

bool compareYear(const Actor& act1, const Actor& act2)
{
	return(act1.year < act2.year);
}

bool compareAward(const Actor& act1, const Actor& act2)
{
	return(act1.award < act2.award);
}

bool compareWinner(const Actor& act1, const Actor& act2)
{
	return(act1.winner < act2.winner);
}

/*This is a template for a reverse-sort, if the user wished to sort in descending order.
*T can be replaced with whichever field needs to be sorted by.
bool compareTDescending
{
return(act1.T > act2.T);
}
*/