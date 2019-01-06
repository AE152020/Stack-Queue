//Kevin Florio CSM20 Fall 2016 Project B
#ifndef Node_H
#define Node_H

#include <memory>   // For shared_pointer
using namespace std;

template<class ItemType>
class Node
{
private:
	ItemType item;
	std::shared_ptr<Node<ItemType> >  next; // Pointer to next node

	Node(const Node<ItemType> & node) {}
	Node<ItemType> & operator = (const Node<ItemType> & node) {}

public:
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, shared_ptr<Node<ItemType> >  nextNodePtr);

	void setItem(const ItemType& anItem);
	void setNext(shared_ptr<Node<ItemType> >  nextNodePtr);

	ItemType getItem() const;
	std::shared_ptr<Node<ItemType> > getNext() const;
}; // End Node

template<class ItemType>
Node<ItemType>::Node()
{
	next = nullptr;
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item{ anItem }, next{ nullptr }
{
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, shared_ptr<Node<ItemType> >  nextNodePtr) :
	item{ anItem }, next{ nextNodePtr }
{
} // end constructor

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
} // end setItem

template<class ItemType>
void Node<ItemType>::setNext(shared_ptr<Node<ItemType> >  nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
} // end getItem

template<class ItemType>
std::shared_ptr<Node<ItemType> > Node<ItemType>::getNext() const
{
	return next;
} // end getNext




#endif

