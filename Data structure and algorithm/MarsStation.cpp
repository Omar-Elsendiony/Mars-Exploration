#include "MarsStation.h"

void MarsStation::AssignErover(Mission* rovermission, ERover* eRover)
{
	eRover->setRoverMission(rovermission);
	rovermission->setEWD(currentDay, eRover->getSpeed());
	Rovers* ptrRover;
	ptrRover = eRover;
	In_execution_rover_list.enqueue(ptrRover);

}


void MarsStation::AssignProver(Mission* rovermission, PRover* pRover)
{
	pRover->setRoverMission(rovermission);
	rovermission->setEWD(currentDay, pRover->getSpeed());
	Rovers* ptrRover;
	ptrRover = pRover;
	In_execution_rover_list.enqueue(ptrRover);
}

MarsStation::MarsStation()
{
	currentDay = 0;
	userInterface = new UI();
}

void MarsStation::AssignMission(FormulationEvent* p)
{
	p->Execute(currentDay); //note that setting the starting of waiting days is done here automatically when creating mission
	bool b;
	char type = p->gettype();
	if (type == 'E')
	{
		Emission* c = p->getEmission();
		EMissionList.enqueue(c);
	}
	else
	{
		Pmission* g = p->getPmission();
		b = PMissionList.enqueue(g);
	}
}


void MarsStation::AssignRover()
{

}


void MarsStation::ExecuteAll()
{
	// Formulating Event and creating missions 
	/////////////////////////
	Event* temp;
	EventList.peek(temp);
	
	if (temp)
	{
		if (temp->getDay() == currentDay)
		{

			while (temp->getDay() == currentDay)
			{
				FormulationEvent* r = dynamic_cast<FormulationEvent*>(temp);
				if (r)
				{
					FormulationEvent* p = (FormulationEvent*)r;
					EventList.dequeue(temp);
					AssignMission(p);
					EventList.peek(temp);
					if (!temp)
					{
						break;
					}
				}
			}

		}

	}
	

	DequeueCheckUpLists();

	// Assign Rovers
	////////////////////////////////////////
	while ((!AvailableERoverList.isEmpty() || !AvailablePRoverList.isEmpty()) && (!EMissionList.IsEmpty() || !PMissionList.isEmpty()))
	{
		Emission* ptrEmission; ERover* PtrErover; PRover* ptrProver; Mission* ptrMission; Rovers* ptrRover;
		Pmission* ptrPmission;
		if (!EMissionList.IsEmpty())
		{
			if (!AvailableERoverList.isEmpty())
			{

				EMissionList.dequeue(ptrEmission);
				AvailableERoverList.dequeue(PtrErover);
				ptrMission = ptrEmission;
				AssignErover(ptrMission, PtrErover);
			}

			else if (!AvailablePRoverList.isEmpty())
			{
				EMissionList.dequeue(ptrEmission);
				AvailablePRoverList.dequeue(ptrProver);
				ptrMission = ptrEmission;
				AssignProver(ptrMission, ptrProver);
			}
		}

		else
		{
			if (!AvailableERoverList.isEmpty())
			{

				PMissionList.dequeue(ptrPmission);
				AvailableERoverList.dequeue(PtrErover);
				ptrMission = ptrPmission;
				AssignErover(ptrMission, PtrErover);
			}

			else if (!AvailablePRoverList.isEmpty())
			{
				PMissionList.dequeue(ptrPmission);
				AvailablePRoverList.dequeue(ptrProver);
				ptrMission = ptrPmission;
				AssignProver(ptrMission, ptrProver);
			}
		}
	}
	
	Rovers* Ptr;
	Mission* M;
	Pmission* PM;
	bool isEmergency, isPolar;
	
	/*if (EM)
	{
			PM = M
	}*/

	if(In_execution_rover_list.Peek(Ptr))
	{
		M = Ptr->getRoverMission();
		if (currentDay == 156)
		{
			bool s = 0;
		}


		while ((M->getFinishDay()) == currentDay)
		{
			/*Emission* EM = dynamic_cast<Emission*> (M);
			if (EM)
			{

			}
			else
			{

			}*/
			
			CompletedMissionList.enqueue(M);
			In_execution_rover_list.dequeue(Ptr);
			int s2;
			if (currentDay == 7)
			{
				s2 = 0;
			}

			if (!EnqueueCheckUpLists(Ptr))
			{
				ERover* Type = dynamic_cast<ERover*>(Ptr);

				if (Type)
				{
					ERover* E = Type;
					AvailableERoverList.enqueue(E);
				}
				else
				{
					PRover* Type2 = dynamic_cast<PRover*>(Ptr);
					//PRover* P = (PRover*)Type;
					AvailablePRoverList.enqueue(Type2);
				}
			}
			In_execution_rover_list.Peek(Ptr); //
			if (!Ptr)
			{
				break;
			}
			M = Ptr->getRoverMission();
		}
	}
	outputSim();
	++currentDay;
}

void MarsStation:: CallInputFile()
{
	userInterface->inputFile(AvailableERoverList, AvailablePRoverList, EventList);
}


void MarsStation::CallOutputChoice()
{
	userInterface->outputSimulationChoice();
}



void MarsStation::outputSim()
{
	userInterface->ConsoleOutput(currentDay, PMissionList, EMissionList, AvailableERoverList, AvailablePRoverList, In_execution_rover_list, CheckUpEmg, CheckUpPolar, CompletedMissionList);
}
bool MarsStation::programEnded()
{
	if (EventList.isEmpty())
	{
		if (PMissionList.isEmpty() && EMissionList.IsEmpty())
		{
			if (In_execution_rover_list.IsEmpty() && CheckUpEmg.isEmpty() && CheckUpPolar.isEmpty())
			{
				return true;
			}
		}
	}
	
	
	return false;
}

void MarsStation::CallOutputFile()
{
	userInterface->OutputFile(CompletedMissionList, AvailableERoverList, AvailablePRoverList);
}

bool MarsStation::EnqueueCheckUpLists(Rovers* Just_Finished_Rover)
{
	Just_Finished_Rover->IncrementMissionsComp();
	if (Just_Finished_Rover->NeedsCheckUp())
	{
		ERover * Type = dynamic_cast<ERover*>(Just_Finished_Rover);
		if (Type)
		{
			ERover* E = Type;
			CheckUpEmg.enqueue(E);
			E->setFinishCheckUp(currentDay);
		}
		else
		{
			PRover* P = dynamic_cast<PRover*>(Just_Finished_Rover);
			CheckUpPolar.enqueue(P);
			P->setFinishCheckUp(currentDay);
		}
		return true;
	}
	return false;

}

void MarsStation::DequeueCheckUpLists()
{
	ERover* E;
	PRover* P;
	if (!CheckUpEmg.isEmpty())
	{
		CheckUpEmg.peek(E);
		int snm;
		if (currentDay == 31)
		{
			snm = 0;
		}
		while (E->getFinishCheckup() == currentDay)
		{
			CheckUpEmg.dequeue(E);
			AvailableERoverList.enqueue(E);
			CheckUpEmg.peek(E);
			if (!E)
			{
				break;
			}
		}
			
		
		
	}

	if (!CheckUpPolar.isEmpty())
	{
		CheckUpPolar.peek(P);
		if (P)
		{
			while (P->getFinishCheckup() == currentDay)
			{
				CheckUpPolar.dequeue(P);
				AvailablePRoverList.enqueue(P);
				CheckUpPolar.peek(P);
				if (!P)
				{
					break;
				}
			}
		}
		
	}
}
