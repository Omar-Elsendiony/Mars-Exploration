#include "Pmission.h"
#include "Queue.h"
#include "Mission.h"
#include <iostream>
using namespace std;

class Mission;
class Pmission;

int main()
{
	LinkedQueue <Pmission> Q1;

	Pmission* P1 = new Pmission(1, 2, 3, 4, 5);
	Q1.enqueue(P1);
	Pmission* P2;
	Q1.dequeue(P2);
	cout << P2->getFormulationDay() << endl;

	return 0;
}