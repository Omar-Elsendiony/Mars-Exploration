#include "PRovers.h"

PRover::PRover(int spd, int Checkupdur, int Ncheckup) :Rovers(spd, Checkupdur, Ncheckup)
{
	number++;
}

int PRover:: number = 0;

int PRover::getNumberPRover()
{
	return number;
}
