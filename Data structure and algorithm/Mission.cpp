#pragma once
#include "Mission.h"

Mission::Mission(int fd, int md, int targetloc, int significance, int Id)
{
	FD = fd;
	SWD = fd;
	MD = md;
	targetlocation = targetloc;
	Significance = significance;
	numberOfmissions++;
	missionID = Id;
	Assigned = false;

}

/////////////////////////////////////////////////////////////

int Mission::numberOfmissions = 0; // static data member initialization

//////////////////////////////////////////////////////////

char Mission::getMissionType()
{
	return missionType;
}

void Mission::setMissionType(char s)
{
	missionType = s;
}

bool Mission::getAssigned()
{
	return Assigned;
}

// setEWD is resposible for calculating most data members of mission

void Mission::setEWD(int CurrentDay, int Speed)
{
	EWD = CurrentDay;
	WD = EWD - SWD;
	Assigned = true;
	ED = 2 * (targetlocation / Speed) / 25 + MD; //v = d/t m/s t= d/v
	CD = FD + WD + ED;
}

int Mission::getEWD()
{
	return EWD;
}

int Mission::getSWD()
{
	return SWD;
}

int Mission::getFinishDay() const
{
	return CD;
}

int Mission::getFormulationDay() const
{
	return FD;
}
int Mission::getMissionId() const
{
	return missionID;
}
int Mission::getWaitingDays() const
{
	return WD;
}
int Mission::getExecutionDays() const
{
	return ED;
}

int Mission::getTargetLoc() const
{
	return targetlocation;
}

int Mission::getSignificance() const
{
	return Significance;
}

int Mission::getMissionDuration() const
{
	return MD;
}

int Mission::getNumberOfmissions()
{
	return numberOfmissions;
}

Mission::~Mission()
{

}