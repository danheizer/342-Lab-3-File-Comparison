/*******************************************************************************
CompareList source code

Stores a pointer to a LinkedList (similar to a head pointer) and includes 
methods for comparing files.

@file       CompareList.h
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/

#include "data.h"
#include "LinkedList.h"
#include "CompareList.h"
#include "Timer.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string.h>

//	If a file has a prime fib match, after a certain number of matching chars, 
//	the program will skip this percentage of the file and resume comparing.
const int AMOUNT_TO_SKIP_FOR_PERFORMANCE = 20;
const int AMOUNT_SEQ_MATCHES_BEFORE_SKIP = 1000;

/**
Constructor that creates a CompareList with a pointer to NULL
*/
CompareList::CompareList()
{
	m_list = NULL;
}

/**
Destructor that calls clear to remove all data
*/
CompareList::~CompareList()
{
	clear();
}

/**
insert(char, int)

Inserts a given char at the end of the LinkedList pointed to by this
CompareList with and int to log where it was found. Can insert to an 
empty list, for all other cases it uses LinkedList insert.
@param char character to insert
@param int byte where char was found
@return bool (true if insert was successful)
*/
bool CompareList::insert(char toAdd, int byteIndex)
{
	//attempting to add the bad char
	if(toAdd == (char)176)
		return false;

	//adding first item
	if(m_list == NULL)
	{
		m_list = new LinkedList(toAdd, byteIndex);
		return true;
	} else {
		//use insert from LinkedList to add to existing list
		m_list->insert(toAdd, byteIndex);
		return true;
	}
}

/**
remove(char)

Removes a given char from the LinkedList pointed to by CompareList. Can remove 
the first element in the list, for all other cases it uses LinkedList remove.
@param char target to be removed
@return bool (true if remove was successful)
*/
bool CompareList::remove(char target)
{
	//No list
	if(m_list == NULL)
		return false;
	
	//First element is the target
	if(m_list->getChar() == target)
	{	
		//Single element List
		if(m_list->getNext() == NULL)
		{
			m_list = NULL;
			return true;

		//Multi-element list
		} else {
			m_list = m_list->getNext();
			return true;
		}	
	}
	//All other cases, call remove from LinkedList
	return m_list->remove(target);
}

/**
remove(int)

Removes a the char at a given index from the LinkedList that the CompareList 
pointer points to. Can remove the first element in the list, for all other 
cases it uses LinkedList remove.
@param int target index of the char to be removed
@return bool (true if remove was successful)
*/
bool CompareList::remove(int targetIndex)
{
	//No elements in list
	if(m_list == NULL)
	{
		return false;
	}
	//First element is target
	if(targetIndex == 1)
	{	
		//exactly one element List
		if(m_list->getNext() == NULL)
		{
			delete m_list;
			m_list = NULL;
			return true;

		//Multi-element list
		} else {		
			LinkedList* temp = m_list;
			m_list = m_list->getNext();
			temp->setNext(NULL);
			delete temp;
			return true;
		}	
	}
	//All other cases, call remove from LinkedList
	return m_list->remove(targetIndex);
	return false;
}
/**
clear

Clears all data by removing each element.
@param none
@return bool (true if success)
*/
bool CompareList::clear()
{
	//Call remove on first element until it returns false
	while(remove(1)){};
	return true;
}

/**
loadFib

Loads a CompareList with chars from a file at a specific byte index. The byte 
index follows the Prime Fibonacci sequence, and will only take data at up to 
the first nine numbers. Ignores whitespace characters at the beginning.
@param string file to be read and loaded
@return void
*/
void CompareList::loadFib(string fileName)
{
	//Create an ifstream from the file and go to the beginning
	ifstream infile(fileName.c_str());
	infile.seekg(0, ios::beg);
	
	//Ignore all leading whitespace
	while(infile.peek() == ' ' || infile.peek() == '\t' 
		|| infile.peek() == '\n' || infile.peek() == '\r')
		      infile.ignore( 1, infile.eof() );

	//Inserts next PrimeFib byte by moving the difference between the current 
	//byte and the next PrimeFib number
	insert(getNthChar(infile, 2), 2);
	insert(getNthChar(infile, 3-2), 3);
	insert(getNthChar(infile, 5-3), 5);
	insert(getNthChar(infile, 13-5), 13);
	insert(getNthChar(infile, 89-13), 89);
	insert(getNthChar(infile, 233-89), 233);
	insert(getNthChar(infile, 1597-233), 1597);
	insert(getNthChar(infile, 28657-1597), 28657);
	insert(getNthChar(infile, 514229-28657), 514229);
	
	infile.close();
}

/**
compareFib

Compares target and prospect CompareLists. Keeps a bool array to store the match
value at each primeFib location. Calls a print function when done.
@param string the file to be compared against the target
@return void
*/
void CompareList::compareFib(string prospectFileName)
{
	//Create CompareList to hold prospectFile bytes
	CompareList prospectFileList;
	prospectFileList.loadFib(prospectFileName);
	
	//Iterators for target and prospect lists
	LinkedList* targetCurrent = m_list;
	LinkedList* prospectCurrent = prospectFileList.m_list;

	//Find how many PrimeFib bytes are being compared, create a bool array 
	int ArraySize = findMin(getSize(), prospectFileList.getSize());
	bool* retVal = new bool[ArraySize]();
	
	//Compare the bytes, log bool value in the array, increment the iterators
	for(int i = 0; i < ArraySize; i++)
	{
		retVal[i] = (targetCurrent->getChar() == prospectCurrent->getChar());
		targetCurrent = targetCurrent->getNext();
	    prospectCurrent = prospectCurrent->getNext(); 
	}
	//Print the results of the PrimeFib comparison
	compareFibResults(retVal, ArraySize, prospectFileList);
	
	//delete the bool array
	delete[] retVal;
}

/**
compareFibResults

Prints out a table the shows byte number, the chars held in the target and 
prospect files, and if they match. Also calculates and shows what percent of 
bytes examined were matches.
@param bool*
@param int boolArraySize
@param CompareList prospect
@return void
*/
void CompareList::compareFibResults(bool* results, int boolArraySize, 
														  CompareList& prospect)
{	
	cout << endl << "Byte Number   Target Char   Prospect Char  Match" << endl;

	//Iterators/counter
	LinkedList* targetCurrent = m_list;
	LinkedList* prospectCurrent = prospect.m_list;
	double numMatches = 0;

	//Print byte number, chars in target and prospect lists, and match result
	for(int i = 0; i < boolArraySize; i++)
	{
		cout << setw(10) << targetCurrent->getIndex() << setw(10);
		//print unique whitespace chars in target
		if(targetCurrent->getChar() == '\n')
			cout << "\\n" << setw(15);
		else if(targetCurrent->getChar() == ' ')
			cout << "space" << setw(15);
		else if(targetCurrent->getChar() == '\t')
			cout << "\\t" << setw(15);
		else if(targetCurrent->getChar() == '\r')
			cout << "\\r" << setw(15);
		else
			cout << targetCurrent->getChar() << setw(15); 
		//print unique whitespace chars in prospect
		if(prospectCurrent->getChar() == '\n')
			cout << "\\n" << setw(11);
		else if(prospectCurrent->getChar() == ' ')
			cout << "space" << setw(11);
		else if(prospectCurrent->getChar() == '\t')
			cout << "\\t" << setw(11);
		else if(prospectCurrent->getChar() == '\r')
			cout << "\\r" << setw(11);
		else
			cout << prospectCurrent->getChar() << setw(11); 
		cout << results[i] << endl;
		
		//update iterators/counter
		targetCurrent = targetCurrent->getNext();
	    prospectCurrent = prospectCurrent->getNext(); 
		if(results[i])
			numMatches++;
	}
	//Calculate and print match result
	double matchPercent = (numMatches / boolArraySize)*100;
	cout << endl << "PrimeFib percent match: " << matchPercent << "%";
	if(matchPercent == 100)
		cout << " (SUSPECT)" << endl;
	else
		cout << " (NOT SUSPECT)" << endl;
}

/**
compareConsecutiveBytes(string, string)

Compares two given files by reading in one byte of each at a time and checking 
them for equality. It ignores leading whitespace, prints the results of the 
comparison when done.
@param string target file
@param string prospect file
@return void
*/
bool CompareList::compareConsecutiveBytes(string targetFileName, 
														string prospectFileName)
{
	int targetSize = getNumBytes(targetFileName);
	int prospectSize = getNumBytes(prospectFileName);
	bool sameSize = targetSize == prospectSize;
	int seqCount = 0; // Count how many sequential matchings chars
	int sequentialMatch  = 0;	//Counter to speed up comparison
	int skipSize = targetSize / AMOUNT_TO_SKIP_FOR_PERFORMANCE;
	if(strcmp(targetFileName.c_str(), prospectFileName.c_str()) == 0)
	{
		cout << "Comparing a file to itself (MATCH CONFIRMED)" << endl;
		return true;
	}
	ifstream infile(targetFileName.c_str());
	ifstream otherFile(prospectFileName.c_str());
	//Ignore all leading whitespace
	while(infile.peek() == ' ' || infile.peek() == '\t' || 
		infile.peek() == '\n' || infile.peek() == '\r')
	{
		      infile.ignore( 1, infile.eof() );
	}
	while(otherFile.peek() == ' ' || otherFile.peek() == '\t' || 
		otherFile.peek() == '\n' || otherFile.peek() == '\r')
	{
		otherFile.ignore(1, otherFile.eof());
	}
	
	//Initialize target and prospect lists
	CompareList targetList;
	CompareList prospectList;
	int byteIndex = 1;			//byte counter
	char targetNextChar;		//target char iterator
	char prospectNextChar;		//prospect char iterator
	while(!infile.eof() && !otherFile.eof())
	{
		//Read chars
		targetNextChar = targetList.getNextChar(infile);
		prospectNextChar = prospectList.getNextChar(otherFile);
		//If not equal, print the byte index and stop comparing
		if(targetNextChar != prospectNextChar)
		{
			cout << "Mismatch found at byte " << byteIndex << " (NOT MATCHING)" 
				 << endl;
			return false;
		}
		//If chars are equal, store them and keep comparing
		//targetList.insert(targetNextChar, byteIndex);
		//prospectList.insert(prospectNextChar, byteIndex);
		byteIndex++;
		sequentialMatch++;
		if(sameSize && sequentialMatch == AMOUNT_SEQ_MATCHES_BEFORE_SKIP)
		{
			if((byteIndex + skipSize) < targetSize)
				infile.ignore(skipSize, EOF);
				otherFile.ignore(skipSize, EOF);
				byteIndex += skipSize;

		}
	}
		cout << "looped to eof" << endl;
	//The end of the smaller file was reached and no mismatches found
	cout << "100% File match (MATCH CONFIRMED)" << endl;
	
	return true;
}
/**
printFileStats(string, string)

Reads in a file and print the type, name, and number of bytes (if it can be 
read).
@param string the name of the file
@param string the file type (target or prospect)
@return void
*/
void CompareList::printFileStats(string filename, string filetype)
{
	ifstream infile(filename.c_str());
	if(!infile)
	{
		cout << filetype <<" File could not be read. " << endl;
	}
	cout << filetype << " File: " << filename << ", "<< getNumBytes(filename) 
	<< " Bytes" << endl;
	
	infile.close();
}

/**
compareFiles(string, string)

Runs comparisons between two given files and prints the results. It prints the 
stats of both files, compares the bytes at the primefib indices, then compares
all the bytes consecutively until a mismatch is found. 
It times both comparisons.
@param string target file name
@param string prospect file name
@return void
*/
void CompareList::compareFiles(string targetFile, string prospectFile)
{
	cout << "------------------------------------------------------------------"
		"-------\n";
	
	//Print stats for both files
	printFileStats(targetFile, "Target");
	printFileStats(prospectFile, "Prospect");

	//Prime Fibonacci byte comparison and results
	cout << "Prime Fibonacci byte comparison results: " << endl;
	Timer Fibtimer;
	Fibtimer.start();
	CompareList target;
	target.loadFib(targetFile);       
	target.compareFib(prospectFile);
	cout << "Runtime for Prime Fibonacci comparison: ";
	Fibtimer.elapsed();
	cout << endl;

	//Consecutive byte comparison and results
	cout << "Consectutive byte results: ";
	Timer consecutiveTimer;
	consecutiveTimer.start();
	CompareList target2;
	target2.compareConsecutiveBytes(targetFile, prospectFile);
	cout << "Runtime for Consecutive Byte Comparison: ";
	consecutiveTimer.elapsed();
}

/**
getNthChar(ifstream&, int)

Ignores a specified amount of chars.
@param ifstream& opened file to be searched
@param int amount to move along in file to find desired char
@return char the char found
*/
char CompareList::getNthChar(ifstream& infile, int increment)
{
	char target = (char)176;
	if(!infile.eof())
	{
		infile.ignore(increment - 1, infile.eof());
		infile >> noskipws >> target;
	}
	return target;
}

/**
getNextChar(ifstream&)

Gets the next byte.
@param ifstream& opened file to be searched
@return char the char found
*/
char CompareList::getNextChar(ifstream& infile)
{
	char target = (char)176;
	if(!infile.eof())
	{
		infile >> noskipws >> target;
	}
	return target;
}

/**
findMax(int, int)

@param int one number
@param int second number
@return int the higher number
*/
int CompareList::findMax(int a, int b)
{	
	if(a > b) 
		return a;
	return b;
}

/**
findMin(int, int)

@param int one number
@param int second number
@return int the lower number
*/
int CompareList::findMin(int a, int b)
{	
	if(a < b) 
		return a;
	return b;
}

/**
getSize

Gets the number of elements in a CompareList
@param none
@return int the size
*/
int CompareList::getSize() const
{
	if(m_list == NULL)
		return 0;
	return m_list->getSize();
}

/**
isInSet

Traverses the list to check for a target char.
@param char target char
@return bool true if target was in the set.
*/
bool CompareList::isInSet(char target)
{
	if(m_list == NULL)
		return false;
	
	LinkedList* current = m_list;
	//Traverse the list
	while(current->getNext() != NULL)
	{
		//Check for target
		if(current->getChar() == target)
			return true;
		//Increment current
		current = current->getNext();

	}
	//Reached end of List
	if(current->getChar() == target)
		return true;
	return false;
}


/**
getNumBytes(string)

Opens a file and counts the numbre of bytes, including leading whitespace.
@param string the file to be counted
@return int the number of bytes
*/
int CompareList::getNumBytes(string filename)
{
	ifstream fileToCount(filename.c_str());
	int numBytes = 0;
	while(!fileToCount.eof())
	{
		numBytes++;
		fileToCount.ignore(1, fileToCount.eof());
	}

	fileToCount.seekg(0, ios::beg);
	fileToCount.close();

	return numBytes;
}

/**
operator=

Sets this to a given CompareList
@param CompareList to be set to
@return CompareList newly set
*/
const CompareList& CompareList::operator=(const CompareList& rhs)
{
	//clear this
	clear();

	//insert all of rhs
	LinkedList* current = rhs.m_list;
	for(int i = 0; i < rhs.getSize(); i++)
	{
		insert(current->getChar(),current->getIndex());
		current = current->getNext();
	}
	return *this;
}

/**
operator==

Indicates if the lists are the same.
@param CompareList
@return bool (true if equal)
*/
bool CompareList::operator==(const CompareList &rhs) const
{
	if(getSize() != rhs.getSize())
		return false;
	return (*m_list == *rhs.m_list);
}

/**
operator<<

Prints a CompareList with opening and closing braces.
@param ostream holds the output
@param CompareList list to be printed
@return ostream& the printed CompareList
*/
ostream& operator<<(ostream &output, const CompareList &a)
{
	if(a.m_list == NULL)
	{
		output << "{}";
	}
	else{
		output << *a.m_list;
	}
	return output;
}


