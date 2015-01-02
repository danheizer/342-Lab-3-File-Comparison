/*******************************************************************************
CompareList header file

@file       CompareList.h
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/

#ifndef COMPARELIST_H
#define COMPARELIST_H

#include <string.h>
#include "LinkedList.h"

class CompareList
{
	friend ostream& operator<<(ostream &output, const CompareList &a);
	
	LinkedList* m_list;

public:
	CompareList();
	~CompareList();

	void loadFib(string filename);					
	void compareFib(string);
	static bool compareConsecutiveBytes(string targetFile, string prospectFile);
	static void printFileStats(string filename, string filetype);
	static void compareFiles(string filename1, string filename2);

	char getNthChar(ifstream&, int);
	char getNextChar(ifstream&);

	int findMax(int a, int b);
	int findMin(int a, int b);
	int getSize() const;
	
	bool operator==(const CompareList &rhs) const;
	bool operator!=(const CompareList &rhs) const { return !(rhs == *this); } 

private:
	void compareFibResults(bool*, int, CompareList&);
	bool isInSet(char);
	static int getNumBytes(string);
	const CompareList& operator=(const CompareList&);
	bool insert(char, int);
	bool remove(char);
	bool remove(int);
	bool clear();
	
};
#endif
