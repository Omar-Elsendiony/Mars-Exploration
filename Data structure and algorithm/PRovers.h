#pragma once
#include <iostream>
#include "Rovers.h"
#include"../Data structure and algorithm/Mission.h"


class PRover : public Rovers
{
	static int number;
public:
	PRover(int spd, int Checkupdur, int Ncheckup);
	int getNumberPRover();
};
