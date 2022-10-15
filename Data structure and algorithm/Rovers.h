#pragma once
#include "Mission.h"

// contains 3 lists :one for m , p , e

class Mission;

class Rovers
{
protected:
	int speed; //in km/hr
	int checkUpDur; //in days and it's the time needed for the rover to be checked 
	int NeedCheckUP; // after how many missions I need to complete to make a checkup
	int  MissionComp; //number of missions completed by the rover, we need it to know it for checkup
	int FinishCheckUp;
	static int incrementID;
	int RoverID;
	Mission* RoverMission;

public:
	Rovers(int spd, int Checkupdur, int Ncheckup);
	void setSpeed(int a);
	virtual void IncrementMissionsComp();
	void setNeedCheckUp(int a);
	int getMissionComp();
	int getNeedCheckUp();
	int getCheckUpDur();
	int getSpeed();
	Mission* getRoverMission();
	virtual ~Rovers();
	void setRoverMission(Mission* a);
	bool isAssigned();
	void setFinishCheckUp(int CurrentDay);
	int getFinishCheckup();
	bool NeedsCheckUp();
	void setRoverID(int);
	int getId();
};
