#pragma once
#include "Emission.h"
#include "Rovers.h"

//Operator Overloading for both Emissions and Erovers since they are sorted in different ways

inline bool operator>(const Emission& E1, const Emission& E2)
{
	return (E1.getPriority() > E2.getPriority());
}

inline bool operator > (Rovers& R1, Rovers& R2)
{
	int CD1 = (R1.getRoverMission())->getFinishDay();
	int CD2 = (R2.getRoverMission())->getFinishDay();
	return (CD1 < CD2); //Notice that I invertedn the > sign because the rovers are sorted ascendingly
	// unlike the Emissions which are sorted descendingly according to priority
}

template <class T>
class PriQ
{

private:

	T* Data[20];
	int Count;

	void ReheapUp(int Index)
	{
		int Parent = GetParentIndex(Index);
		if (Parent >= 0)
		{
			if (*(Data[Index]) > * (Data[Parent]))
			{
				Exchange(Parent, Index);
				ReheapUp(Parent);
			}
		}

	}

	void Exchange(int i1, int i2)
	{
		T* temp = Data[i2];
		Data[i2] = Data[i1];
		Data[i1] = temp;
	}

	void ReheapDown(int Index)
	{
		int LeftChild = GetLeftChildIndex(Index);
		int RightChild = GetRightChildIndex(Index);
		int Largest = Index;

		if (LeftChild <= Count) //if left subtree exists
			if (*(Data[LeftChild]) > * (Data[Largest]))
				Largest = LeftChild;
		if (RightChild <= Count) //if right subtree exists
			if (*(Data[RightChild]) > * (Data[Largest]))
				Largest = RightChild;

		if (Largest != Index)
		{
			Exchange(Largest, Index);
			ReheapDown(Largest);
		}

	}

	int GetLeftChildIndex(int parent)
	{
		return ((2 * parent) + 1);
	}

	int GetRightChildIndex(int parent)
	{
		return ((2 * parent) + 2);
	}

	int GetParentIndex(int child)
	{
		return ((child - 1) / 2);
	}

public:

	PriQ()
	{
		Count = -1;
	}

	void enqueue(T*& Element) 
	{
		Data[++Count] = Element;
		ReheapUp(Count);
	}

	bool dequeue(T*& Element)
	{
		if (!IsEmpty())
		{
			Element = Data[0];
			Data[0] = Data[Count];
			Count--;
			ReheapDown(0);
			return true;
		}
		else
		{
			Element = nullptr;
			return false;
		}
			
	}

	void getCount(int& C)
	{
		C = Count;
	}

	bool IsEmpty()
	{
		return (Count == -1);
	}

	bool Peek(T*& Element)
	{
		if (!IsEmpty())
		{
			Element = Data[0];
			return true;
		}
		else
		{
			Element = nullptr;
			return false;
		}
	}

};
