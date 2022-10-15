#include "../Data structure and algorithm/Rovers.h"


Rovers::Rovers(int spd, int Checkupdur, int Ncheckup)
{
	speed = spd;
	checkUpDur = Checkupdur;
	NeedCheckUP = Ncheckup;
	incrementID++;
	setRoverID(incrementID);
	MissionComp = 0;
}

int Rovers::incrementID = 0;
// 5 4 
void Rovers::setRoverID(int i)
{
	RoverID = i;
}

void Rovers::setRoverMission(Mission* a)
{
	RoverMission = a;
}


Mission* Rovers::getRoverMission()
{
	return RoverMission;
}

void Rovers::setSpeed(int a)
{
	speed = a;
}

int Rovers::getSpeed()
{
	return speed;
}


bool Rovers::isAssigned() //is rover is Assigend to a mission or no and this function is made for potential use in future 
{
	if (this->RoverMission)
		return true;
	else return false;
}

int Rovers::getCheckUpDur()
{
	return checkUpDur;
}

int Rovers::getMissionComp()
{
	return MissionComp;
}

void Rovers::IncrementMissionsComp()
{
	MissionComp++;
}

void Rovers::setNeedCheckUp(int a)
{
	NeedCheckUP = a;
}

int Rovers::getNeedCheckUp()
{
	return NeedCheckUP;
}

Rovers::~Rovers()
{

}

void Rovers::setFinishCheckUp(int CurrentDay)
{
	FinishCheckUp = checkUpDur + CurrentDay;
}

int Rovers::getFinishCheckup()
{
	return FinishCheckUp;
}

bool Rovers::NeedsCheckUp()
{
	if (MissionComp != 0)
		return(MissionComp % NeedCheckUP == 0);
	return false;
}

int Rovers::getId()
{
	return RoverID;
}
