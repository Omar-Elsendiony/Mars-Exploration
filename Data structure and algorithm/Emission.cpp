#include "Emission.h"

#define Significance_Weight 100
#define TargetLoc_Weight 0.01

Emission::Emission(int fd, int md, int targetloc, int significance, int Id) : Mission(fd, md, targetloc, significance, Id)
{
	setPriority();
	setMissionType('E');
}

void Emission::setPriority()
{
	int TargetLoc = getTargetLoc();
	int Significance = getSignificance();
	int MD = getMissionDuration();
	int FD = getFormulationDay();
	Priority = (Significance_Weight * Significance / (TargetLoc_Weight * TargetLoc * MD * FD));
}

int Emission::getPriority() const
{
	return Priority;
}
