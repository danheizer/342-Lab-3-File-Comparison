/*******************************************************************************
LinkedList header file

@file       LinkedList.h
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;


class LinkedList {
	friend istream& operator>>(istream &input, LinkedList &a);
	friend ostream& operator<<(ostream &output, const LinkedList &a);

	LinkedList *m_next;		
	data *m_data;			

	bool insert(LinkedList*);	

public:
	LinkedList();
	LinkedList(const LinkedList&);
	LinkedList(char, int);
	LinkedList(data);
	LinkedList(data*, LinkedList*);
	LinkedList(data* inData);
	~LinkedList();

	bool insert(char, int);			
	bool remove(char);
	bool remove(int);
	
	int getSize() const;
	char getChar(){ return m_data->getChar(); }
	int getIndex(){ return m_data->getInt(); }
	LinkedList* getNext(){ return m_next; }
	
	void setData(data* dataPtr){ m_data = dataPtr; } 
	void setNext(LinkedList* next) { m_next = next; }
	
	const LinkedList& operator=(const LinkedList&);
	bool operator==(const LinkedList &rhs) const;
	bool operator!=(const LinkedList &rhs) const { return !(*this==rhs); }
};
#endif
