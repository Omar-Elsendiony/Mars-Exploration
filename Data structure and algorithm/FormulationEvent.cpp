#include "FormulationEvent.h"
//
FormulationEvent::FormulationEvent(char m, int d, int missionId, int Location, int f, int s) :Event(missionId, d)
{
	Mtype = m;
	Tlocation = Location;
	missionDuration = f;
	sig = s;
	emission = nullptr;
	pmission = nullptr;

}

void FormulationEvent::Execute(int fd)
{

	if (Mtype == 'E')
	{

		emission = new Emission(fd, missionDuration, Tlocation, sig, missionID);
	}
	else if (Mtype == 'P')
	{

		pmission = new Pmission(fd, missionDuration, Tlocation, sig, missionID);

		//return //Pmission(fd, missionDuration, Tlocation, missionID);
	}
}
Emission* FormulationEvent::getEmission()
{
	return emission;
}

Pmission* FormulationEvent::getPmission()
{
	return pmission;
}

char FormulationEvent::gettype()
{
	return Mtype;
}

FormulationEvent::~FormulationEvent()
{

}


