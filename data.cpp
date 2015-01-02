/*******************************************************************************
data source code

The source file for a data node used in the LinkedList class. It is used to hold 
character bytes found in files, along with the byte number where it was found.

@file       data.cpp
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/

#include "data.h"



/**
Constructor that sets m_char to a given char and m_int to a given int
@param char the character byte found
@param int the index where it was found
*/
data::data(char character, int index)
{
	m_char = character;
	if(index >= 0)
		m_index = index;
	else m_index = 0;
}

/**
Constructor that sets m_char and m_int to the char and int in a given data 
object
@param data& the data object to be copied
*/
data::data(const data& rhs)
{
	m_char = rhs.m_char;
	m_index = rhs.m_index;
}

const data& data::operator=(const data& rhs)
{
	m_char = rhs.m_char;
	m_index = rhs.m_index;
	return *this;
}
/**
operator>

Indicates if a 'this' object is greater than a given data object, based on if
the char in it comes later in the ASCII/UNICODE sequence
@param data& the data to be compared
@return bool (true if 'this' is greater)
*/
bool data::operator>(const data& rhs)
{
	return m_char > rhs.m_char;
}

/**
operator<

Indicates if a 'this' object is less than a given data object, based on if
the char in it comes earlier in the ASCII/UNICODE sequence
@param data& the data to be compared
@return bool (true if 'this' is less)
*/
bool data::operator<(const data& rhs)
{
	return m_char < rhs.m_char;
}

/**
operator==

Indicates if the chars held in 'this' data object and given data obejct are the 
same, ignore the index
@param data& the data to be compared
@return bool true if chars are equal
*/
bool data::operator==(const data& rhs)
{
	return m_char == rhs.m_char;
}

/**
operator!= 

Indicates if the chars held in 'this' data object and given data obejct are not
the same, ignores the index
@param data&
@return bool (true if chars are not equal)
*/
bool data::operator!=(const data& rhs)
{
	return m_char != rhs.m_char;
}

/**
operator<<

Prints the char held in 'this' with a single leading space.
@param ostream& to hold the output
@param data& the data to be printed
@return ostream& that has a space and a char (eg. ' c') 
*/
ostream& operator<<(ostream& out, const data& data)
{
	out << " " << data.m_char;
	return out;
}
