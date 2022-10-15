#pragma once
#include "Event.h"
class FormulationEvent :public Event
{
private:
	int Tlocation; //the mission’s target location (in kilometers from the base station)
	int missionDuration; // number of days needed to fulfill the mission requirements at target location
	int sig; // mission’s significance
	char Mtype;
	Emission* emission;
	Pmission* pmission;
public:
	FormulationEvent(char m, int x, int y, int t, int f, int s);
	//void Execute();
	Emission* getEmission();
	Pmission* getPmission();
	void Execute(int fd);
	char gettype();
	~FormulationEvent();

};
