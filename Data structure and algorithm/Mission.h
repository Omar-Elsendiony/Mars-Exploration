#pragma once
#include "Rovers.h"
class Mission
{
protected:
	int FD; //Formulation day of the mission
	int MD; //Mission Duration
	int ED; //Execution Days: The amount of days in execution for the mission 
	int leftDays; // the amount of days till the mission ends
	int targetlocation;
	int WD; //Waiting Days before the mission is executed
	int SWD; // start of the waiting days
	int EWD; // end of the waiting days 
	int CD; //Completion day is the finish time
	int Significance;
	// Equation of consumptionDays = 2*(TargetLocation*RoverSpeed)/25 +MD;
	//Rovers* R; //Rover assigned to the mission
	bool Assigned;
	char missionType;
	int missionID;
	static int numberOfmissions;

public:
	Mission(int fd, int md, int targetloc, int significance, int Id);
	bool getAssigned();
	int getMissionDuration() const;
	void setEWD(int CurrentDay, int Speed);
	int getSWD();
	int getEWD();
	int getFinishDay() const;
	static int getNumberOfmissions();
	virtual int getFormulationDay() const;
	int getMissionId() const;
	int getWaitingDays() const;
	int getExecutionDays() const;
	int getTargetLoc() const;
	int getSignificance() const;
	char getMissionType();
	void  setMissionType(char s);
	virtual ~Mission();
};
