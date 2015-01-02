/*******************************************************************************
Lab3testmain

Executes unit/regression testing for CompareList and data.
@file       lab3testmain.cpp
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include "data.h"
#include "CompareList.h"
#include <cstdlib>
#include "Timer.h"
#include "TestList.h"

#if defined(WIN32)
	#include "windows.h"
#else
	#include <sys/time.h>
#endif

using namespace std;


//void testDataConstructors();
//void testCompareListConstructors();
//void testCompareListInsertAndRemoveChar();
//void testCompareListRemoveInt();
//void testCompareListGetSize();
//testCompareListInsertAndRemoveChar();
//testCompareListRemoveInt();
			
int main()
{	
	//CompareList test1;
	//test1.loadFib(infile);
	//cout << test1 << endl;

	//CompareList test2;
	//test2.loadFib(infile2);
	//test1.compareFib(test2);
	
	/* 
	ifstream file1;
	file1.open("sampledata.txt", ios::in );
	
	ifstream file2;
	file2.open("sampledata2.txt", ios::in);

	CompareList test1;
	test1.loadFib(file1);

	CompareList test2;
	test2.loadFib(file2);
	
	cout << "test1: " << test1 << endl;
	cout << "test2: " << test2 << endl;

	test1.remove(6);

	cout << test1 << endl;
	cout << "Calling clear: " << endl;
	test1.clear();
	cout << test1 << endl;
//	test2.compareFib(file2);
	
	/*CompareList test3;
	cout << "LoadingFib..." << endl;
	test3.loadFib(file1);
	cout << "ComparingFib..." << endl;
	
	test3.compareFib(file2);
	cout << "Fib Comparison Complete" << endl;*/
	//file1.close();
	//file2.close();
	
	//CompareList test20;
	//CompareList test21;
	
	//test20.loadFib("sampledata.txt");
	//cout << test20 << endl;
	//test21.loadFib("sampledata2.txt");
	//cout << test21 << endl;

	//test20.compareFib("sampledata2.txt");
	/*
	Timer compareTime;
	
	SYSTEMTIME start = compareTime.getTime();



	SYSTEMTIME end = compareTime.getTime();
	compareTime.elapsed(start, end);
	*/

	TestList::testData();
	TestList::testRemoveChar();
	TestList::testRemoveInt();
	TestList::testInsert();
	TestList::testEquals();
	return 1;






}












/**
void testDataConsSingleChar();

/**
Test if the insert(char) and remove(char) functions of CompareList is operating as intended.
Removing a char that appears multiple times will remove the first occurence of the char. 
Special Cases for remove
	Valid:
		Removing First Element
		Removing a Middle Element
		Removing last Element
		
	Invalid:
		*Single Element List
		Remove a char that isn't in the list

Returns true if all cases operated as intended.
*/
/**
void testCompareListInsertAndRemoveChar()
{
	cout << "************ Tests for CompareList.insert(char) *********** " << endl;
	CompareList testRemove('a');
	for(char c = 'b'; c <= 'e'; ++c)
		testRemove.insert(c);
	
	cout << "Starting list, should be { a b c d e}: " << testRemove << endl;

	cout << "************ Tests for CompareList.remove(char) *********** " << endl;

	testRemove.remove('a');
	cout << "Deleting first element, should be { b c d e}: " << testRemove << endl;

	testRemove.remove('e');
	cout << "Deleting last element, should be { b c d}: " << testRemove << endl;

	testRemove.remove('c');
	cout << "Deleting middle element, should be { b d}: " << testRemove << endl;

	cout << "Remove char not in list (Should be 0): "
			<< testRemove.remove('X') << endl; 
	cout << endl;



	
	for(char c = 'a'; c <= 'z'; c++)
	{
		test.insert(c);
	}
	cout << test << endl;
	test.remove('z');
	test.remove('a');
	test.remove('x');
	test.remove('b');
	cout << test << endl;

	CompareList test2;
	test2.loadPrimeFib("sampledata.txt");
	cout << test2 << endl;
	test2.remove('F');
	cout << "test2: " << test2 << endl;
}
/**
Test if the remove(char) function of CompareList is operating as intended.
Removing a char that appears multiple times will remove the first occurence of the char. 
Special Cases
	Valid:
		Removing First Element
		Removing a Middle Element
		Removing last Element
		
	Invalid:
		*Single Element List
		Remove an index above bounds
		Remove a negative index
		Remove the 0 index

Returns true if all cases operated as intended.
*/
/**
void testCompareListRemoveInt()
{
	cout << "************ Tests for CompareList.remove(int) *********** " << endl;
	// Create list holding chars a-e
	CompareList testRemove('a');
	for(char c = 'b'; c <= 'e'; ++c)
		testRemove.insert(c);
	
	testRemove.remove(1);
	cout << "Deleting first element, should be { b c d e}: " << testRemove << endl;

	testRemove.remove(5);
	cout << "Deleting last element, should be { b c d}: " << testRemove << endl;

	testRemove.remove(2);
	cout << "Deleting middle element, should be { b d}: " << testRemove << endl;
	cout << "Following tests should all return 0: " << endl;
	cout << "Remove index larger than size: "
			<< testRemove.remove(200) << endl; 
	cout << "Remove negative index: " << testRemove.remove(-2) << endl;
	cout << "Remove 0 index: " << testRemove.remove(0) << endl;
	cout << endl;
}
*/