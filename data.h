/*******************************************************************************
data header file

@file       data.h
@author     Martha Pidcock
@author	    Dan Heizer
@section	ASSIGNMENT CSS 342A Lab 3
@section	DUE_DATE 9 Feb 2014
*/

#ifndef DATA_H
#define	DATA_H

#include <iostream>
using namespace std;


class data{
	friend ostream& operator<<(ostream& out, const data&);

	char m_char;
	int m_index;

public:
	data(char, int);
	data(const data& rhs);


	char getChar(){ return m_char; }
	int getInt(){ return m_index; }
	void setChar(char character){ m_char = character; }
	void setInt(int index){ m_index = index; }

	const data& operator=(const data&);
	bool operator>(const data& rhs);
	bool operator<(const data& rhs);
	bool operator==(const data& rhs);
	bool operator!=(const data& rhs);
};
#endif
