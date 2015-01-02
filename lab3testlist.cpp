/*******************************************************************************
Lab3testlist

Holds methods to test the CompareList class and data class.
@file       lab3testlist.cpp
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/
#include "TestList.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "data.h"
#include "CompareList.h"
#include <cstdlib>
#include "Timer.h"

#if defined(WIN32)
	#include "windows.h"
#else
	#include <sys/time.h>
#endif
using namespace std;

/**
Tests the core functionality of the Data class.
@param none
return true if all methods behave as expected
*/
bool TestList::testData()
{
	cout << "Testing the data class" << endl;
	//Test basic constructor
	data testCons('c', 5);
	if(testCons.getInt() != 5 || testCons.getChar() != 'c')
	{
		cout << "Unintended behavior: data(char, int)" << endl;
		return false;
	}
	data testNegativeInt('x', -10);
		if(testNegativeInt.getInt() != 0)
	{
		cout << "Unintended behavior: (negative int) data(char, int)" 
			<< endl;
		return false;
	}
	//Test copy constructor and == / !=
	data testCopyConsAndEquals(testCons);
	if(testCopyConsAndEquals != testCons)
	{
		cout << "Unintended behavior: data(data&) OR operator !=" << endl;
		return false;
	}

	//Test less than / greater than
	data testGreaterChar('d', 3);
	data testLesserChar('a', 9);
	if(!(testCons > testLesserChar) || !(testCons < testGreaterChar)
			|| testCons < testLesserChar || testCons > testGreaterChar)
	{
		cout << "Unintended behavior: operator < OR operator >" << endl;
		return false;
	}
	data testEqualsAssignment('d', 78);
	testCons = testEqualsAssignment;
	if(testCons != testEqualsAssignment)
	{
		cout << "Unintended behavior: Assignment =" << endl;
		return false;
	}
	cout << "Data tests completed successfully" << endl;
	cout << endl;
	return true;
}
/**
Tests the core functionality of the remove(char) function
@param none
return true if all cases behave as expected
*/
bool TestList::testRemoveChar()
{
	cout << "Testing remove(char) " << endl;
	//Create and populate a list to remove from
	CompareList test;
	for(int i = 0; i < 26; i++)
	{
		test.insert( i + 97, i + 1);
	}
	test.remove('a');

	//remove head of list
	if(test.isInSet('a'))
	{
		cout << "Unintended Behavior: Remove head of list" << endl;
		return false;
	}
	
	//Remove a char that isn't in the List
	if(test.remove((char)197))
	{
		cout << "Unintended Behavior: Removing char not in list" << endl;
		return false;
	}

	//Removing the last element of the list
	test.remove('z');
	if(test.isInSet('z'))
	{
		cout << "Unintended Behavior: Removing last element in list" 
			<< endl;
		return false;
	}
	cout << "Remove(char) tests completed successfully" << endl;
	cout << endl;
	return true;
}

/**
Tests the core functionality of the remove(int) function
@param none
return true if all cases behave as expected
*/
bool TestList::testRemoveInt()
{
	cout << "Testing remove(int) " << endl;
	//Create and populate a list to remove from
	CompareList test;
	for(int i = 0; i < 26; i++)
	{
		test.insert( i + 97, i + 1);
	}
	test.remove(1);

	//remove head of list
	if(test.isInSet('a'))
	{
		cout << "Unintended Behavior: Remove head of list" << endl;
		return false;
	}
	
	//Remove a char that isn't in the List
	if(test.remove(197))
	{
		cout << "Unintended Behavior: Removing index outside bounds"
			<< endl;
		return false;
	}

	//Removing the last element of the list
	test.remove(25);
	if(test.isInSet('z'))
	{
		cout << "Unintended Behavior: Removing last element in list" 
			<< endl;
		return false;
	}
	cout << "Remove(int) tests completed successfully" << endl;
	cout << endl;
	return true;
}

/**
Tests the core functionality of the insert function

return true if all cases behave as expected
*/
bool TestList::testInsert()
{
	cout << "Testing Insert" << endl;
	CompareList test;
	//Test inserting first element
	test.insert('a', 0);

	if(!(test.isInSet('a')))
	{
		cout << "Unintended behavior: Inserting first element" << endl;
		return false;
	}
	//Insert from lower case a to the ~ char
	for(int i = 65; i < 127; i++)
	{
		if(!(test.insert(i,i)))
		{
			cout << "Unintended behavior: Inserting char "<< (char)i <<
				endl;
			return false;
		}
	}

	cout << "Insert tests completed successfully" << endl;
	cout << endl;
	return true;
}

/**
Tests the core functionality of the == operator
@param none
return true if all cases behave as expected
*/
bool TestList::testEquals()
{
	cout << "Testing ==, !=, and = operators" << endl;
	CompareList test;
	CompareList test2;
	for(char i = 97; i < 123; i++)
	{
		test.insert(i,i);
		test2.insert(i,i);
	}
	
	if(!(test == test2))
	{
		cout << "Unintended behavior: == Operator" << endl;
		return false;
	}
	cout << "Basic Equality test success" << endl;
	CompareList test3;
	if(test == test3)
	{
		cout << "Unintended behavior: == Operator (false positive)" << endl;
		return false;
	}
	cout << "False Equality test success" << endl;
	if(test != test2)
	{
		cout << "Unintended behavior: != Operator" << endl;
		return false;
	}
	cout << "basic != test success" << endl;
	if(!(test != test3))
	{
		cout << "Unintended behavior: != Operator (false negative)" << endl;
		return false;
	}
	cout << "False != test success" << endl;
	CompareList testFile;
	testFile.loadFib("s0.txt");
	test3 = testFile;
	if(test3 == testFile)
		cout << "operator= test success" << endl;
	cout << "Operator == and != tests completed successfully " << endl;
	cout << endl;
	return true;
}