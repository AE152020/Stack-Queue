//Kevin Florio CSM20 Fall 2016 Project B
#ifndef LinkedQueue_H
#define LinkedQueue_H

#include "Node.h"
#include "PrecondViolatedExcept.h"
#include <memory>

template<class ItemType>
class LinkedQueue
{
private:
	void assignLinkedQueue(const LinkedQueue& aQueue) const; 

	mutable std::shared_ptr<Node<ItemType> > frontPtr; // Allows modification in const
	mutable std::shared_ptr<Node<ItemType> > backPtr; // Allows modification in const

	bool _enqueue(const ItemType& newEntry) const;
	bool _dequeue() const;

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue& aQueue);
	LinkedQueue& operator =(const LinkedQueue& aQueue);

	~LinkedQueue();

	bool isEmpty() const;

	bool enqueue(const ItemType& newEntry);
	bool dequeue();

	ItemType peekFront() const throw(PrecondViolatedExcept);
};

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue() // Destructor
{
	frontPtr = std::shared_ptr<Node<ItemType> >();
}

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue() {} // Default constructor

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const
{
	return (frontPtr.get() == nullptr);
}

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue& aQueue)
{
	this->assignLinkedQueue(aQueue);
}

template<class ItemType>
LinkedQueue<ItemType>& LinkedQueue<ItemType>::operator = (const LinkedQueue& aQueue)
{
	this->assignLinkedQueue(aQueue);
	return (*this);
}


template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry) // To add item to Queue
{
	return this->_enqueue(newEntry);
}

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue() // To remove front item from Queue
{
	return this->_dequeue(); 
}

template<class ItemType>
bool LinkedQueue<ItemType>::_enqueue(const ItemType& newEntry) const
{
	auto newNodePtr = std::shared_ptr<Node<ItemType> >(new Node<ItemType>(newEntry));
	if (isEmpty())
		frontPtr = newNodePtr; // The queue was empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	return true;
}

template<class ItemType>
bool LinkedQueue<ItemType>::_dequeue() const
{
	auto result = false;
	if (!isEmpty())
	{
		auto nodeToDeletePtr = frontPtr; // Queue is not empty
		if (frontPtr == backPtr) // Special case only one node in queue
		{
			frontPtr.reset(); // Set front and back ptr to nullptr
			backPtr.reset();
		}
		else
			frontPtr = frontPtr->getNext();

		// Maintain an accurate reference count for first node
		nodeToDeletePtr->setNext(nullptr); // Removed node will be deallocated when method ends
		result = true;
	}
	return result;
}

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const throw(PrecondViolatedExcept) // Get copy of front of Queue
{
	auto ableTopeek = (frontPtr.get() != nullptr);
	if (ableTopeek)
	{
		return frontPtr->getItem();
	}
	else
	{
		auto message = "peekFront - Queue empty";
		throw PrecondViolatedExcept(message);
	}

}

template<class ItemType>
void LinkedQueue<ItemType>::assignLinkedQueue(const LinkedQueue& aQueue) const // Copy Queue
{
	int i;
	std::vector<ItemType> data_backup;
	while (!aQueue.isEmpty())
	{
		data_backup.push_back(aQueue.peekFront());
		aQueue._dequeue();
	}

	while (!this->isEmpty()) this->_dequeue();

	for (i = 0; i < data_backup.size(); i++)
	{
		this->_enqueue(data_backup[i]);
		aQueue._enqueue(data_backup[i]);
	}
}

#endif
