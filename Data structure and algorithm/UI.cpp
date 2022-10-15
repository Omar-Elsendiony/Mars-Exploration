#pragma once
#include "UI.h"
void UI::inputFile(LinkedQueue<ERover>& AvailableERoverList, LinkedQueue<PRover>& 
	AvailablePRoverList, LinkedQueue<Event>& EventList)
{
	input.open("inputFile2.txt");

	if (input.fail())
	{
		cerr << "Error!! Opening file" << endl;
		exit(1);
	}

	//int MRN; // Mountainous rovers number
	int PRN; // Polar Rovers number
	int ERN; // Emergency Rovers number
	input >> PRN >> ERN;
	int SP;  // polar rover speed
	int SE; // Emergency Rover Speed
	int N; //number of missions the rovers do before checkup
	int CP; // Checkup Polar
	int CE; //checkup Emergency
	input >> SP >> SE;
	input >> N >> CP >> CE;
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	for (int i = 0; i < PRN; i++)
	{
		PRover* P;
		P = new PRover(SP, CP, N);
		AvailablePRoverList.enqueue(P);
	}
	for (int i = 0; i < ERN; i++)
	{
		ERover* E = new ERover(SE, CE, N);
		AvailableERoverList.enqueue(E);
	}

	// setting static data member
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	//int SM; //mountainous Rover Speed

	//int CM; //checkup mountainous duration

	//int AutoP;
	int numberEvents; //number of events

	//input >> AutoP;
	input >> numberEvents;
	char eventType;
	char missionType;
	int fd, ID, TLOC, MDUR, SIG;

	// Creating an event list


	while (!input.eof())
	{
		Event* e;
		input >> eventType;
		if (eventType == 'F')
		{
			//add to event list
			// F event list
			input >> missionType;
			input >> fd;
			input >> ID;
			input >> TLOC;
			input >> MDUR;
			input >> SIG;
			e = new FormulationEvent(missionType, fd, ID, TLOC, MDUR, SIG);
			EventList.enqueue(e);
		}
		else if (eventType == 'X')
		{
		}
		else if (eventType == 'P')
		{
		}
	}
}

void UI::outputSimulationChoice() //chooses the type of simulation from choice
{
	cout << "Choose Program interface(from 1 to 3 inclusive):" << endl;
	cout << "1-Interactive Mode" << endl;
	cout << "2- Step by Step Mode" << endl;
	cout << "3- Silent Mode" << endl;
	int choiceN;
	cin >> choiceN;
	while (!(choiceN >= 1 && choiceN <= 3))
	{
		cout << "Error! The choice you entered is not within range." << endl;
		cout << "Enter again:";
		cin >> choiceN;
	}
	this->choice = choiceN;
	if (choice == 1)
	{
		cout << "Interactive Mode" << endl;
	}
	else if (choice == 2)
	{
		cout << "Step-By-Step Mode" << endl;
	}
	else if (choice == 3)
	{
		cout << "Silent Mode" << endl;
	}
	cout << "Simulation Starts" << endl;
}


void UI::EnterPressed() const
{
	
		char a;
		a = _getche();
		while (a != 13)
		{
			a = _getche();
		}
}


void UI::ConsoleOutput(int dayMarsStation, LinkedQueue<Pmission> PMissionList, PriQ<Emission> EMissionList, LinkedQueue<ERover> AvailableERoverList, LinkedQueue<PRover> AvailablePRoverList, PriQ<Rovers> In_execution_rover_list, LinkedQueue<ERover> CheckUpEmg, LinkedQueue<PRover> CheckUpPolar, LinkedQueue <Mission> CompletedMissionList) //needs day,mission list(s),rover list(s)
{
	if (choice != 3)
	{
		int countP, countE;
		PMissionList.getCount(countP);  // DS peek enqueue dequeue
		EMissionList.getCount(countE);
		//////////////////////////////////////
		// int count
		// enqueue ++count;
		++countE;
		cout << "Current Day:" << dayMarsStation << endl;

		cout << countE + countP << " " << "Waiting Missions: ";
		// Reserving Variables
		Emission* tempEMission; int tempID;
		cout << "[";
		if (EMissionList.dequeue(tempEMission))
		{
			cout << tempEMission->getMissionId();
		}

		while (EMissionList.dequeue(tempEMission))
		{
			cout << ',';
			tempID = tempEMission->getMissionId();
			cout << tempID;
		}
		cout << "] (";
		Pmission* tempPMission;
		if (PMissionList.dequeue(tempPMission))
		{
			cout << tempPMission->getMissionId();
		}

		while (PMissionList.dequeue(tempPMission))
		{
			cout << ',';
			tempID = tempPMission->getMissionId();
			cout << tempID;
		}
		cout << ')';
		cout << endl;
		////////////// END OF THE FIRST LINE ///////////////////////////////////
		//EnterPressed();
		cout << "-------------------------------------------------------------------------" << endl;
		int countR;
		In_execution_rover_list.getCount(countR);
		countR++;
		cout << countR << " " << "In-Execution Missions/Rovers: [";
		ERover* tempERover;
		PRover* tempPRover;
		Rovers* tempR;
		bool enter = 1;
		if (!In_execution_rover_list.dequeue(tempR))
		{
			enter = 0;
		}
		LinkedQueue<ERover> sublist1;
		LinkedQueue<PRover> sublist2;
		bool reLoop = 1;
		if (enter)
		{
			while (reLoop)
			{
				tempERover = dynamic_cast<ERover*>(tempR);
				if (tempERover)
				{
					sublist1.enqueue(tempERover);
				}
				else
				{

					tempPRover = dynamic_cast<PRover*>(tempR);
					if (tempPRover)
					{
						sublist2.enqueue(tempPRover);
					}
				}
				if (In_execution_rover_list.IsEmpty())
				{
					reLoop = 0;
				}
				else
				{
					In_execution_rover_list.dequeue(tempR);
				}
			}
			////////////////////////////////////////////////
			int number;
			if (sublist1.dequeue(tempERover))
			{
				number = tempERover->getRoverMission()->getMissionId();
				cout << number << "/" << tempERover->getId();
			}

			while (sublist1.dequeue(tempERover))
			{
				cout << ", " << tempERover->getRoverMission()->getMissionId() << "/" << tempERover->getId();
			}
			cout << "] (";
			if (sublist2.dequeue(tempPRover))
			{
				number = tempPRover->getRoverMission()->getMissionId();
				cout << number << "/" << tempPRover->getId();
			}
			while (sublist2.dequeue(tempPRover))
			{
				cout << ", " << tempPRover->getRoverMission()->getMissionId() << "/" << tempPRover->getId();
			}


			cout << ")" << endl;
		}
		else
		{
			cout << "] ()" << endl;
		}
		////////////////////// END OF THE SECOND LINE ///////////////////////////////
		//EnterPressed();
		cout << "-------------------------------------------------------------------------" << endl;

		AvailableERoverList.getCount(countE);
		AvailablePRoverList.getCount(countP);

		cout << countE + countP << " Available Rovers: [";
		if (AvailableERoverList.dequeue(tempERover))
		{
			cout << tempERover->getId();
		}

		while (AvailableERoverList.dequeue(tempERover))
		{
			cout << ", " << tempERover->getId();
		}
		cout << "] (";
		if (AvailablePRoverList.dequeue(tempPRover))
		{
			cout << tempPRover->getId();
		}
		int m;
		while (AvailablePRoverList.dequeue(tempPRover))
		{
			if (dayMarsStation == 90)
			{
				m = 0;
			}
			cout << ", " << tempPRover->getId();
		}
		cout << ")";
		cout << endl;
		//////////////////// END OF THIRD LINE /////////////////////////////////////
		//EnterPressed();
		cout << "-------------------------------------------------------------------------" << endl;
		CheckUpEmg.getCount(countE);
		CheckUpPolar.getCount(countP);
		//++countE;
		cout << countE + countP << " In-Checkup Rovers: [";
		int s = 0;
		
		if (CheckUpEmg.dequeue(tempERover))
		{
			cout << tempERover->getId();
		}

		while (CheckUpEmg.dequeue(tempERover))
		{
			cout << ", " << tempERover->getId();
		}
		cout << "] (";
		if (CheckUpPolar.dequeue(tempPRover))
		{
			cout << tempPRover->getId();
		}

		while (CheckUpPolar.dequeue(tempPRover))
		{
			cout << ", " << tempPRover->getId();
		}
		int y = 0;
		cout << ")";
		cout << endl;
		////////////////// END OF FOURTH LINE //////////////////////////////
		//EnterPressed();
		cout << "-------------------------------------------------------------------------" << endl;
		Mission* mm; int missionCount;
		CompletedMissionList.getCount(missionCount);
		//missionCount++;
		cout << missionCount << " Completed Missions: ";

		//cout<< mm->getMissionId();
		Emission* FlagEMission;
		Pmission* FlagPmission;
		LinkedQueue<Emission> E;
		LinkedQueue <Pmission> P;
		LinkedQueue<Mission>tempQueue;

		while (CompletedMissionList.dequeue(mm))
		{
			FlagEMission = dynamic_cast<Emission*>(mm);
			if (FlagEMission)
			{
				E.enqueue(FlagEMission);
			}
			else
			{
				tempQueue.enqueue(mm);
			}
		}
		while (tempQueue.dequeue(mm))
		{
			FlagPmission = dynamic_cast<Pmission*>(mm);
			if (FlagPmission)
			{
				P.enqueue(FlagPmission);
			}
		}
		cout << "[";
		if (E.dequeue(tempEMission))
		{
			cout << tempEMission->getMissionId();
		}

		while (E.dequeue(tempEMission))
		{
			cout << "," << tempEMission->getMissionId();
		}
		cout << "] (";
		if (P.dequeue(tempPMission))
		{
			cout << tempPMission->getMissionId();
		}
		while (P.dequeue(tempPMission))
		{
			cout << "," << tempPMission->getMissionId();
		}
		cout << ")";
		cout << endl;
		
		cout << "-------------------------------------------------------------------------" << endl;
		///////////////////////////////////////////////////////////////////////////////////////////////////
		if (choice == 1)
		{
			EnterPressed();
		}
		else if (choice == 2)
		{

			// Do not forget to try Sleep of windows.h
			Sleep(1000);
		}
	}
}
//void OutputFile(LinkedQueue<Mission> CompletedMissionList, LinkedQueue<ERover> AvailableER, LinkedQueue<PRover> AvailablePR);
void UI::OutputFile(LinkedQueue<Mission> CompletedMissionList, LinkedQueue<ERover> AvailableER, LinkedQueue<PRover> AvailablePR)
{
	out.open("outputFile.txt");
	out << "CD" << "\t" << "ID" << "\t" << "FD" << "\t" << "WD" << "\t" << "ED" << endl;
	Mission* toPrint;
	Emission* E;
	Pmission* P;
	int sumWaitingDays = 0;
	int sumExecutionDays = 0;
	int Ecount = 0;
	int Pcount = 0;
	int TotalCount = 0;
	while (CompletedMissionList.dequeue(toPrint))
	{
		E = dynamic_cast<Emission*> (toPrint);
		if (E)
		{
			Ecount++;
		}
		else
		{
			P = dynamic_cast<Pmission*> (toPrint);
			if (P)
			{
				Pcount++;
			}
		}
		out << toPrint->getFinishDay() << "\t" << toPrint->getMissionId() << "\t" << toPrint->getFormulationDay() << "\t" << toPrint->getWaitingDays() << "\t" << toPrint->getExecutionDays();
		out << endl;
		sumWaitingDays += toPrint->getWaitingDays();
		sumExecutionDays += toPrint->getExecutionDays();
		TotalCount++;
	}
	out << "Missions: " << toPrint->getNumberOfmissions() << " [P: ";
	out << Pcount << ", " << "E: " << Ecount << "]" << endl;
	ERover* EEE;
	PRover* CCE;

	AvailableER.peek(EEE);
	AvailablePR.peek(CCE);
	int num1, num2;
	num1 = EEE->getNumberERovers();
	num2 = CCE->getNumberPRover();

	int RoverTotal = num1+ num2; //Total nuumber of Rovers;

	out << "Rovers: "<<RoverTotal <<" [P: "<< num2<<", "<<" E: "<< num1<<"]"<<endl;
	double AvgW = 0.00;
	double AvgE = 0.00;
	if (TotalCount != 0)
	{
		 AvgW = (double)sumWaitingDays / TotalCount;
		 AvgE = (double)sumExecutionDays / TotalCount;
	}
	
	out << "Avg Wait = " << AvgW << ", Avg Exec = " << AvgE;
	out.close();
	cout << "Simulation end, Output file created" << endl;
}
