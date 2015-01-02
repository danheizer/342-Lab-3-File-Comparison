/*******************************************************************************
Timer source code

Determines runtime of a method.
@file       Timer.cpp
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/

#include <iostream>
#include <cstdlib>

#include	"Timer.h"

using namespace std;

/**
Constructor that uses start time
*/
Timer::Timer()
{
	start();
}

//For use in windows
#if	defined( WIN32 )
	#include "windows.h"

	static SYSTEMTIME startTime; // holds start time

	/**
	start

	Gets time to start.
	@param none
	@return void
	*/
	void Timer::start()
	{
		GetSystemTime(&startTime);
	}

	/**
	elapsed

	Finds the difference from start to now and prints it.
	@param none
	@return void
	*/
	void Timer::elapsed()
	{
		SYSTEMTIME now;      // holds current time
		GetSystemTime(&now);

		//converts to filetime
		FILETIME start, end; 
		SystemTimeToFileTime(&startTime, &start);
		SystemTimeToFileTime(&now, &end);

		//does the math necessary for subtracting times
		__int64 delta = *((__int64 *)(&end)) - *((__int64 *)(&start));
		float seconds = float(delta)/10000000.0f;
		cout <<  seconds << " sec" << endl;
	}

//for use in Linux
#else
	#include <sys/time.h>

	static timeval startTime;  // holds start time

	/**
	start

	Gets time to start.
	@param none
	@return void
	*/
	void Timer::start()
	{
		gettimeofday( &startTime, 0 );
	}

	/**
	elapsed

	Finds the difference from start to now and prints it.
	@param none
	@return void
	*/
	void Timer::elapsed()
	{
		struct timeval now;		// holds current time
		gettimeofday(&now, 0);

		// finds difference in time using seconds and microseconds
		long seconds, microseconds; 
		seconds  = now.tv_sec  - startTime.tv_sec;
		microseconds = now.tv_usec - startTime.tv_usec;
		if (microseconds < 0)
			microseconds += 1000000 ;  // correct for roll over

		 cout << seconds << " sec, " << microseconds << " microsec." << endl;
	}

#endif