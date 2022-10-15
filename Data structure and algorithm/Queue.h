#pragma once
#include "Node.h"

template <typename T>
class LinkedQueue
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int Count;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(T*& newEntry);
	bool dequeue(T*& frntEntry);
	bool peek(T*& frntEntry)  const;
	void getCount(int& C);
	void print() const;
	~LinkedQueue();

	//copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ);
};

/*
Function: Queue()
The constructor of the Queue class.
*/
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	Count = 0;
}

template <typename T>
void LinkedQueue<T>::getCount(int& C)
{
	C = Count;
}


template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/*Function:enqueue
Adds newEntry at the back of this queue.
Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::enqueue(T*& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	Count++;
	return true;
} // end enqueue

template <typename T>
bool LinkedQueue<T>::dequeue(T*& frntEntry)
{
	if (isEmpty())
	{
		frntEntry = nullptr;
		return false;
	}

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	Count--;
	return true;
}

template <typename T>
bool LinkedQueue<T>::peek(T*& frntEntry) const
{
	if (isEmpty())
	{
		frntEntry = nullptr;
		return false;
	}
		

	frntEntry = frontPtr->getItem();
	return true;

}

/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T* temp;
	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided
Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	Count = LQ.Count;
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}

}

