#include <iostream>
#include "Vehicle.h" //Do I need this if I declared vehicle as a friend class?
#include "Recursive.h"
#include <vector>
#include <string>
#include <algorithm>


//Recursive search by year
int Recursive::searchRec(int query, const std::vector<Vehicle>& veh, int start, int end, int size)
{
	//Check base cases for start and end.
	if (query == veh[start].year)
	{
		return(start);
	}
	else if (query == veh[end].year)
	{
		return(end);
	}
	else
	{
		int mid = size / 2;
		if ( mid == 0) //no more iterations can be done
			return(-1);
		else if (query == veh[mid].year) //Check the midpoint. It seems to get overlooked without this.
		{
			return(mid); //Midpoint is the appropriate value.
		}
		else if (query < veh[mid].year) //year is smaller than the midpoint
		{
			return(searchRec(query, veh, start, mid, (size - (size - mid))));
		}
		else
		{
			return(searchRec(query, veh, (end - mid), end, (size - mid)));
		}
	}
}

//Recursive search by model
int Recursive::searchRec(std::string query, const std::vector<Vehicle>& veh, int start, int end, int size)
{
	if (query == veh[start].model)
	{
		return(start);
	}
	else if (query == veh[end].model)
	{
		return(end);
	}
	else
	{
		int mid = size / 2;
		if (mid == 0) //no more iterations can be done
			return(-1);
		else if (query == veh[mid].model)
		{
			return(mid); //Midpoint is the appropriate value.
		}
		else if (query < veh[mid].model) //model is closer to the start of the alphabet
		{
			return(searchRec(query, veh, start, mid, (size - (size - mid))));
		}
		else
		{
			return(searchRec(query, veh, (end - mid), end, (size - mid)));
		}
	}
}

//Recursive search by make
int Recursive::searchRec(std::string query, std::string type, const std::vector<Vehicle>& veh, int start, int end, int size)
{
	if (query == veh[start].make)
	{
		return(start);
	}
	else if (query == veh[end].make)
	{
		return(end);
	}
	else
	{
		int mid = size / 2;
		if (mid == 0) //no more iterations can be done
			return(-1);
		else if (query == veh[mid].make)
		{
			return(mid); //Midpoint is the appropriate value.
		}
		else if (query < veh[mid].make) //model is closer to the start of the alphabet
		{
			return(searchRec(query, veh, start, mid, (size - (size - mid))));
		}
		else
		{
			return(searchRec(query, veh, (end - mid), end, (size - mid)));
		}
	}
}

//Iterative search by year
int Recursive::searchIter(int& query, const std::vector<Vehicle>& veh)
{
	int size = veh.size();
	int start = 0;
	int end = veh.size() - 1;
	int mid = end / 2;
	bool searching = true; //Changes to false when size is 1. 
	while (searching)
	{
		if (size == 1)
		{
			searching = false; //Either it's found this iteration or it's not there.
		}
		if (query == veh[mid].year)
		{
			return(mid);
		}
		else if (query < veh[mid].year) //Less than the mid
		{
			//Change end and midpoint, re-run. No change to start. DON'T FORGET TO CHANGE SIZE
			end = mid;
			mid = end / 2;
			size = end - start;
		}
		else
		{
			//Change start point to midpoint, midpoint is the point between the start and endpoint. No change to endpoint.
			start = mid; //mid + 1?
			mid = (end - (end - start) / 2);
			size = end - start;
		}
	}
	return(-1);
}

//Iterative search by model
int Recursive::searchIter(std::string query, const std::vector<Vehicle>& veh)
{
	int size = veh.size();
	int start = 0;
	int end = veh.size() - 1;
	int mid = end / 2;
	bool searching = true;

	while (searching)
	{
		if (size == 1)
		{
			searching = false;
		}
		if (query == veh[mid].model)
		{
			return(mid);
		}
		else if (query < veh[mid].model) //Less than the mid
		{
			//Change end and midpoint, re-run. No change to start.
			end = mid;
			mid = end / 2;
			size = end - start;
		}
		else
		{
			//Change start point to midpoint, midpoint is the point between the start and endpoint. No change to endpoint.
			start = mid; //mid + 1?
			mid = (end - (end - start) / 2);
			size = end - start;
		}
	}
	return(-1);
}

//Iterative search by make
int Recursive::searchIter(std::string query, std::string make, std::vector<Vehicle>& veh)
{
	int size = veh.size();
	int start = 0;
	int end = veh.size() - 1;
	int mid = end / 2;
	bool searching = true;

	while (searching)
	{
		if (size == 1)
		{
			searching = false;
		}
		if (query == veh[mid].make)
		{
			return(mid);
		}
		else if (query < veh[mid].make) //Less than the mid
		{
			//Change end and midpoint, re-run. No change to start.
			end = mid;
			mid = end / 2;
			size = end - start;
		}
		else
		{
			//Change start point to midpoint, midpoint is the point between the start and endpoint. No change to endpoint.
			start = mid; //mid + 1?
			mid = (end - (end - start) / 2);
			size = end - start;
		}
	}
	return(-1);
}
