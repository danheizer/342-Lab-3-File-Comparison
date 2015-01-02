/*******************************************************************************
Lab3main source code

Runs comparison tests between two files - a target and its prospective match. 
The first test matches the only the first 9 prime Fibonacci offset bytes 
(2, 3, 5, 13, 89, 233, 1597, 28657, 514229), reports what characters are at 
those bytes in each file, if they match, and the percentage match of the files 
based on those bytes. The second test matches all bytes consecutively and 
reports either at what byte a mismatch was found or that the files match 
completely as far as they go. The time taken for both tests is measured and 
compared.
@file       lab3main.cpp
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
#include <string.h>

#if defined(WIN32)
	#include "windows.h"
#else
	#include <sys/time.h>
#endif

using namespace std;



int main(int argc, char* argv[] )
{
	//Create arrays to hold all file names, grouped by letter
	string targetFileNames [2] = { "s0.txt", "t0.txt" };
	string cProspectFileNames [8] = { "c1.txt", "c2.txt", "c3.txt", "c4.txt",
		"c5.txt", "c6.txt", "c7.txt", "c8.txt" };
	string tProspectFileNames [9] = { "t0.txt", "t1.txt", "t2.txt", "t3.txt", 
		"t4.txt", "t5.txt", "t6.txt", "t7.txt", "t8.txt" };
	string sProspectFileNames [15] = { "s0.txt", "s1.txt", "s2.txt", "s3.txt", 
		"s4.txt", "s5.txt", "s6.txt", "s7.txt", "s8.txt",  "s9.txt", "s10.txt",
		"s11.txt", "s12.txt", "s13.txt", "s154.txt" };
	string hbProspectFileNames [3] = { "h1.txt", "h2.txt", "b0.txt" };
	string csProspectFileName = "cs.txt";
	
	//Compares target files to all c*.txt files
	for(int targetFileNum = 0; targetFileNum < 2; targetFileNum++)
	{
		for(int prospectFileNum = 0; prospectFileNum < 8; prospectFileNum++)
		{
			CompareList::compareFiles(targetFileNames[targetFileNum], 
				cProspectFileNames[prospectFileNum]);
		}
	}
	
	//Compares target files to all t*.txt files
	for(int targetFileNum = 0; targetFileNum < 2; targetFileNum++)
	{
		for(int prospectFileNum = 0; prospectFileNum < 9; prospectFileNum++)
		{
			CompareList::compareFiles(targetFileNames[targetFileNum], 
				tProspectFileNames[prospectFileNum]);
		}
	}


	//Compares target files to all s*.txt files
	for(int targetFileNum = 0; targetFileNum < 2; targetFileNum++)
	{
		for(int prospectFileNum = 0; prospectFileNum < 15; prospectFileNum++)
		{
			CompareList::compareFiles(targetFileNames[targetFileNum], 
				sProspectFileNames[prospectFileNum]);
		}
	}


	//Compares target files to all h*.txt and b*.txt files
	for(int targetFileNum = 0; targetFileNum < 2; targetFileNum++)
	{
		for(int prospectFileNum = 0; prospectFileNum < 3; prospectFileNum++)
		{
			CompareList::compareFiles(targetFileNames[targetFileNum], 
				hbProspectFileNames[prospectFileNum]);
		}
	}


	//Compares target files to cs.txt
	for(int targetFileNum = 0; targetFileNum < 2; targetFileNum++)
	{
		for(int prospectFileNum = 0; prospectFileNum < 1; prospectFileNum++)
		{
			CompareList::compareFiles(targetFileNames[targetFileNum], 
				csProspectFileName);
		}
	}

}
