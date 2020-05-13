#pragma once
#define uint unsigned int
#define DataSize 4
#define MaxBitIndex 127
#include <iostream>
#include <string>
using namespace std;

class QInt
{
private:
	uint data[DataSize];

public:
	QInt();

	/*
		--------------------
		---Manipulate bit---
		--------------------
	*/
	//Get a bit value from specific index in range(0, DataSize)
	char getBit(char index);
	//Set a bit value from specific index in range(0, DataSize)
	//Value is only 0 or 1, if value is not 0 it will convert to 1
	void setBit(char index, char value);

	/*
		--------------------
		---Basic operator---
		--------------------
	*/
	//Add this object with the other
	QInt operator + (QInt other);
	//Subtract this object with the other
	QInt operator - (QInt other);
	//Multiply this object with the other
	QInt operator * (QInt other);
	//Divide this object with the other
	QInt operator / (QInt other);

	//Change sign of QInt number
	QInt operator - ();

	/*
		--------------------
		--Bitwise operator--
		--------------------
	*/
	//Bitwise AND operator
	QInt operator & (QInt other);
	//Bitwise OR operator
	QInt operator | (QInt other);
	//Bitwise XOR operator
	QInt operator ^ (QInt other);
	//Bitwise NOT operator
	QInt operator ~ ();

	/*
		--------------------
		--Bitshift operator-
		--------------------
	*/
	//Left shift logical by amount bit(s)
	QInt operator << (int amount);
	//Left shift arithmetic by amount bit(s)
	QInt operator >> (int amount);
	//Rotate left by 1 bit
	QInt rol();
	QInt ror();

	/*
		--------------------
		--Compare operator--
		--------------------
	*/
	//Return is this object greater than the other
	bool operator > (QInt other);
	//Return is this object less than the other
	bool operator < (QInt other);
	//Return is this object greater or equal to the other
	bool operator >= (QInt other);
	//Return is this object less or equal to the other
	bool operator <= (QInt other);
	//Return is this object equal to the other
	bool operator == (QInt other);
	//Return is this object different to the other
	bool operator != (QInt other);

	/*
		--------------------
		---Assign operator--
		--------------------
	*/
	//Assign other QInt object's data to this object
	QInt operator = (QInt other);
	//Convert int to QInt object
	QInt operator = (int other);

	/*
		--------------------
		----Convert Base----
		--------------------
	*/
	//Convert this object to binary string
	string toBinary();
	//Convert this object to decimal string
	string toDec();
	//Convert this object to hexadecimal string
	string toHex();
	//Convert binary string to QInt object
	void fromBinary(string bin);
	//Convert decimal string to QInt object
	void fromDec(string dec);
	//Convert hexadecimal string to QInt object
	void fromHex(string hex);

	/*
		--------------------
		---------IO---------
		--------------------
	*/
	//Print this object in base 10
	friend ostream& operator << (ostream& out, const QInt& number);
	//Input this object in base 10
	friend istream& operator >> (ostream& in, QInt& number);
};

