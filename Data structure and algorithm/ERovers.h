#pragma once
#include <iostream>
#include "Rovers.h"
#include"Emission.h"


class ERover : public Rovers
{
private:
	static int numberERovers;
public:
	ERover(int spd, int Checkupdur, int Ncheckup);
	int getNumberERovers();


};
