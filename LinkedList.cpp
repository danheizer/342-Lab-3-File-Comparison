/*******************************************************************************
LinkedList source code

A list node that holds a pointer to the next LinkedList node and a pointer to a 
data node tht holds a char and an int. LinkedList does not have a head node, it
is pointed to by CompareList to handle empty lists and removal of the first 
element.

@file       LinkedList.cpp
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/

#include "data.h"
#include "LinkedList.h"
#include "CompareList.h"
#include <fstream>
#include <iomanip>
#include <iostream>

/**
Default constructor that creates an empty list
*/
LinkedList::LinkedList()
{
	CompareList();
}

/**
Copy constructor that creates a LinkedList from a given LinkedList
@param LinkedList& the LinkedList to be copied
*/
LinkedList::LinkedList(const LinkedList& rhs)
{
	m_next = NULL;
	for(const LinkedList* current = &rhs; current != NULL; 
	current = current->m_next) {
		LinkedList* temp = new LinkedList(*current->m_data);
		insert(temp);
	}
}

/**
Constructor that creates a LinkedList with a given char and a given int
@param char character for the list to hold
@param int index where the char was found
*/
LinkedList::LinkedList(char inChar, int byteIndex)
{
	m_next = NULL; 
	m_data = new data(inChar, byteIndex);
}

/**
Constructor that creates a LinkedList with a pointer to a given data object as
its only item.
@param data inData
*/


LinkedList::LinkedList(data inData)
{
	m_next = NULL; 
	*m_data = inData;
}

LinkedList::LinkedList(data* inData)
{
	m_next = NULL; 
	m_data = inData;
}
/**
Constructor that creates a LinkedList with a pointer to a given data object and 
a pointer to the next object.
@param data* inData
@param LinkedList* the next LinkedList
*/
LinkedList::LinkedList(data* inData, LinkedList* nextPtr)
{
	m_next = nextPtr;
	m_data = inData;
}

/**
Destructor that deletes the LinkedList by removing the first element in the 
list until the list is empty.
*/
LinkedList::~LinkedList()
{
	while(m_next != NULL) {
		//First element is stored
		LinkedList* firstElementInList = m_next;
		//First element becomes the second element
		m_next = firstElementInList->m_next;
		//Delete first element
		firstElementInList->m_next = NULL;
		delete firstElementInList;
	}
	delete m_data;
}


/** 
insert(char, int)

Inserts a char to the LinkedList. Creates an object with the given char and 
calls insert(LinkedList*) to put it in. Requires the use of CompareList
to insert to an empty list.
@param char to be inserted
@param int index the char was found
@return bool (true if insert was successful)
*/
bool LinkedList::insert(char toAdd, int byteIndex)
{
	LinkedList* temp = new LinkedList(toAdd, byteIndex);
	return insert(temp);
}

/**
insert(data*)

Inserts a list element to the LinkedList. Helper function for insert(char, int). 
@param LinkedList* element that is inserted
@return bool (true if insert was successful)
*/
bool LinkedList::insert(LinkedList* toAdd)
{	
	//create element to traverse list
	LinkedList* current = this;	

	//go until current is the last element
	while(current->m_next != NULL)
		current = current->m_next;
	
	//create a new element with the data*, have the last node point to it
	//LinkedList* temp = new LinkedList(toAdd);
	current->m_next = toAdd; 

	return true;
}

/**
remove(char)

Removes char from the LinkedList by searching for target char. Only removes
the first instance if there is more than one occurance. Requires the use of
CompareList to remove the first element in the list.
@param char target to be removed
@return bool (true if insert was successful)
*/
bool LinkedList::remove(char target)
{
	//iterators to track previous and current nodes
	LinkedList* previous = NULL;
	LinkedList* current = this;

	//go until the current node points to NULL
	while(current->m_next != NULL) 
	{
		//if the target is at the current node
		if(current->m_data->getChar() == target)
		{
			//have previous node point to current next node
			previous->m_next = current->m_next;
			return true;
		}

		//target not found, update previous and current
		previous = current;
		current = current->m_next;
	}
	//target found at last node
	if(current->m_data->getChar() == target)
	{
		//previous node points to NULL
		previous->m_next = NULL;
		return true;
	}

	//target not in list
	return false;
}

/**
remove(int)

Removes a data from the LinkedList by finding the node at a given index. 
Requires the use of CompareList to remove the first element in the list.
@param int index of char to be removed
@return bool (true if insert was successful)
*/
bool LinkedList::remove(int targetIndex)
{
	//invalid index
	if(targetIndex > getSize() + 1|| targetIndex < 1)
	{
		return false;
	}

	//iterators to track previous and current nodes
	LinkedList* previous = NULL;
	LinkedList* current = this;
	//counts through the nodes
	int indexCounter = 1;

	//go until the current node points to NULL
	while(current->m_next != NULL) 
	{
		//at target index
		if(indexCounter == targetIndex)
		{
			//have previous node point to current next node
			LinkedList* temp = current;
			delete temp;
			previous->m_next = current->m_next;
			
			return true;
		}
		//target not found, update iterators an counter
		previous = current;
		current = current->m_next;
		indexCounter++;
	}
	//target index is last node
	if(targetIndex == indexCounter)
	{
		//previous node points to NULL
		delete current;
		previous->m_next = NULL;
		
		return true;
	}

	//target index never reached
	return false;
}

/**
getSize

Gets the number of elements in a LinkedList
@return int the number of nodes in the list
*/
int LinkedList::getSize() const
{
	
	int retVal = 1;		 //cannot have size 0
	for(LinkedList* current = m_next; current != NULL; 
	current = current->m_next)
		retVal++;
	return retVal;
}

/**
operator==

Indicates if all the elements are the same in this list are the same as a given
LinkedList
@param LinkedList& list to be compared
@return bool (true if LinkedLists are equal)
*/
bool LinkedList::operator==(const LinkedList &rhs) const
{
	if(getSize() != rhs.getSize())
		return false;
	
	//Create objects to iterate through the list
	LinkedList* lhsCurrent = new LinkedList(m_data);
	LinkedList* rhsCurrent = new LinkedList(rhs.m_data);
	
	//While both lists have the same data
	while(lhsCurrent->getChar() == rhsCurrent->getChar() 
			&& lhsCurrent->m_next != NULL && rhsCurrent->m_next != NULL)
	{
		//Increment each list
		lhsCurrent = lhsCurrent->m_next;
		rhsCurrent = rhsCurrent->m_next;
		//Check if the newly incremented lists are equal
		if(lhsCurrent->getChar() != rhsCurrent->getChar())
			return false;
	}
	//Loop exits when either m_next is NULL, verify that both are NULL.

	//If all previous elements are the same and the next doesnt exist
	if(lhsCurrent->m_next == NULL && rhsCurrent->m_next == NULL) 
		return true;
	
	return false;
		
}

/**
operator<<

Prints list with opening and closing curly braces.
@param ostream& holds the oputput
@param LinkedList& list to be outputted
@return ostream& with data from the LinkedList
*/
ostream& operator<<(ostream &output, const LinkedList &a)
{
	output << "{";
	for(const LinkedList* current = &a; current != NULL; 
	current = current->m_next)
		output << *current->m_data;
	output << "}";
	return output;
}

/**
operator>>

Input operator that can add characters from keyboard input
@param istream& takes input
@param LinkedList& the list input is added to
@return istream& the list that has the input
*/
istream& operator>>(istream &input, LinkedList &a){
	char toAdd;
	while(true) {
		input >> toAdd;
		a.insert(toAdd, 0);
	}
	return input;
}
