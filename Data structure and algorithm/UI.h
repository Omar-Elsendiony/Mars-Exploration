#pragma once

// Choosing Simulation mode
//Input operation is done hereee
//Output if this mode is chosen
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include "MarsStation.h"
#include "FormulationEvent.h"
#include "ERovers.h"
#include "Rovers.h"
#include "PRovers.h"
#include "Mission.h"
#include "Emission.h"
#include "Queue.h"
#include "PriQ.h"
#include <string.h>
#include <conio.h>
using namespace std;

class MarsStation;

class UI
{
private:
	ofstream out;
	ifstream input;
	int choice;
	
	//void ConsoleOutputUtility();
public:
	void inputFile(LinkedQueue<ERover>&, LinkedQueue<PRover>&, LinkedQueue<Event>&);
	void outputSimulationChoice();
	//outputs based on the choice of program interface
	void OutputFile(LinkedQueue<Mission> CompletedMissionList, LinkedQueue<ERover> AvailableER, LinkedQueue<PRover> AvailablePR);
	void ConsoleOutput(int dayMarsStation, LinkedQueue<Pmission> PMissionList, PriQ<Emission> EMissionList, LinkedQueue<ERover> AvailableERoverList, LinkedQueue<PRover> AvailablePRoverList, PriQ<Rovers> In_execution_rover_list, LinkedQueue<ERover> CheckUpEmg, LinkedQueue<PRover> CheckUpPolar, LinkedQueue <Mission> CompletedMissionList);
	void EnterPressed() const; 

};

