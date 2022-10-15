#pragma once
#include "PMission.h"
Pmission::Pmission(int fd, int md, int targetloc, int Id, int signficance) : Mission(fd, md, targetloc, Id, signficance)
{
	setMissionType('P');
}


