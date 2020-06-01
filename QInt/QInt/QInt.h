#pragma once
#define DataSize 4
#define MaxArrayIndex 3
#define MaxBitIndex 127

#include <iostream>
#include "StringFunction.h"

class QInt
{
private:
	uint data[DataSize];
public:
	QInt();
	QInt(int n);
	/*
		--------------------
		---Manipulate bit---
		--------------------
	*/
	//Get a bit value from specific index in [0, MaxBitIndex]
	char getBit(char index) const;
	//Set a bit value from specific index in [0, DataSize)
	//Value is only 0 or 1, if value is not 0 it will convert to 1
	void setBit(char index, char value);

	/*
		--------------------
		---Basic operator---
		--------------------
	*/
	//Add this object with the other	
	QInt operator + (QInt other) const;
	//Subtract this object with the other
	QInt operator - (QInt other) const;
	//Multiply this object with the other
	QInt operator * (QInt other) const;
	//Divide this object with the other
	QInt operator / (QInt other) const;
	//Modulo this object with other
	QInt operator % (QInt other) const;

	//Change sign of QInt number
	QInt operator - () const;
	//Cast QInt to int

	/*
		--------------------
		--Bitwise operator--
		--------------------
	*/
	//Bitwise AND operator
	QInt operator & (QInt other) const;
	//Bitwise OR operator
	QInt operator | (QInt other) const;
	//Bitwise XOR operator
	QInt operator ^ (QInt other) const;
	//Bitwise NOT operator
	QInt operator ~ () const;

	/*
		--------------------
		--Bitshift operator-
		--------------------
	*/
	//Left shift logical by amount bit(s)
	QInt operator << (int amount) const;
	//Left shift arithmetic by amount bit(s)
	QInt operator >> (int amount) const;
	//Rotate left by 1 bit
	QInt rol(int amount) const;
	QInt ror(int amount) const;

	/*
		--------------------
		--Compare operator--
		--------------------
	*/
	int compare(QInt other) const;
	//Return is this object greater than the other
	bool operator > (QInt other) const;
	//Return is this object less than the other
	bool operator < (QInt other) const;
	//Return is this object greater or equal to the other
	bool operator >= (QInt other) const;
	//Return is this object less or equal to the other
	bool operator <= (QInt other) const;
	//Return is this object equal to the other
	bool operator == (QInt other) const;
	//Return is this object different to the other
	bool operator != (QInt other) const;

	/*
		--------------------
		---Assign operator--
		--------------------
	*/
	//Assign other QInt object's data to this object
	QInt& operator = (QInt other);
	//Convert int to QInt object
	QInt& operator = (int other);

	/*
		--------------------
		----Convert Base----
		--------------------
	*/
	//Convert this object to binary string
	string toBinary() const;
	//Convert this object to decimal string
	string toDec() const;
	//Convert this object to hexadecimal string
	string toHex() const;
	//Convert binary string to QInt object
	void fromBinary(string bin);
	//Convert decimal string to QInt object
	void fromDec(string dec);
	//Convert hexadecimal string to QInt object
	void fromHex(string hex);
	int toInt();

	/*
		--------------------
		---------IO---------
		--------------------
	*/
	//Print this object in base 10
	friend ostream& operator << (ostream& out, const QInt& number);
	//Input this object in base 10
	friend istream& operator >> (istream& in, QInt& number);
};

