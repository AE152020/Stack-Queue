//Kevin Florio CSM20 Fall 2016 Project B
#ifndef LinkedStack_H
#define LinkedStack_H

#include <memory>
#include "Node.h"
using namespace std;

template<class ItemType>
class LinkedStack
{
private:
	void assignLinkedStack(const LinkedStack& aStack) const;
	mutable shared_ptr<Node<ItemType> > topPtr; // Allows modification in const

	bool _push(const ItemType& newItem) const;
	bool _pop() const;

public:
	LinkedStack();
	LinkedStack(const LinkedStack<ItemType>& aStack);
	LinkedStack & operator = (const LinkedStack<ItemType>& aStack);

	~LinkedStack();

	bool isEmpty() const;

	bool push(const ItemType& newItem);
	bool pop();

	ItemType peek() const throw(PrecondViolatedExcept);
};

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() {} // Default constructor

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack) // Copy constructor
{
	this->assignLinkedStack(aStack);
}

template<class ItemType>
LinkedStack<ItemType>& LinkedStack<ItemType>::operator =(const LinkedStack<ItemType>& aStack) // Copy constructor
{
	this->assignLinkedStack(aStack);
	return (*this);
}

template<class ItemType> // Push function
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	return this->_push(newItem);
}

template<class ItemType> // Push function
bool LinkedStack<ItemType>::pop()
{
	return this->_pop();
}

template<class ItemType> // Push function
bool LinkedStack<ItemType>::_push(const ItemType& newItem) const
{
	auto newNodePtr = shared_ptr<Node<ItemType> >(new Node<ItemType>(newItem, topPtr));
	topPtr = newNodePtr;

	return true;
}

template<class ItemType>
bool LinkedStack<ItemType>::_pop() const
{
	auto result = false;
	if (!isEmpty())
	{
		auto nodeToDeletePtr = topPtr; // Stack is not empty, delete top
		topPtr = topPtr->getNext();

		nodeToDeletePtr->setNext(nullptr); // Return deleted node

		result = true;
	}
	return result;
}

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
	if (isEmpty())
		throw PrecondViolatedExcept("peek() called with empty stack");
	else
		return topPtr->getItem();
}

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return (topPtr.get() == nullptr);
}

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	topPtr = std::shared_ptr<Node<ItemType> >();
}

template<class ItemType>
void LinkedStack<ItemType>::assignLinkedStack(const LinkedStack<ItemType>& aStack) const
{
	int i;
	std::vector<ItemType> data_backup;
	while (!aStack.isEmpty())
	{
		data_backup.push_back(aStack.peek());
		aStack._pop();
	}

	while (!this->isEmpty()) this->_pop();

	for (i = data_backup.size() - 1; i >= 0; i--)
	{
		this->_push(data_backup[i]);
		aStack._push(data_backup[i]);
	}
}


#endif

