#include"ERovers.h"
#include"Mission.h"

ERover::ERover(int spd, int Checkupdur, int Ncheckup) : Rovers(spd, Checkupdur, Ncheckup)
{
	numberERovers++;
}
int ERover::numberERovers = 0;

int ERover::getNumberERovers()
{
	return numberERovers;
}