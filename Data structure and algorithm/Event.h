#pragma once
//inputs are put in the event list
#include "Mission.h"
#include "Emission.h"
#include "PMission.h"

class Event
{
protected:
	int Eventday;//event day
	int missionID; //mission Id
public:
	Event(int m, int d)
	{
		missionID = m;
		Eventday = d;
	}
	int getDay()
	{
		return Eventday;
	}

	virtual void Execute(int fd) = 0;

	~Event()
	{

	}
};
