#pragma once
#include "Mission.h"

class Emission : public Mission
{
private:
	double Priority;

public:
	Emission(int fd, int md, int targetloc, int Id, int significance);
	void setPriority();
	int getPriority() const;
};
