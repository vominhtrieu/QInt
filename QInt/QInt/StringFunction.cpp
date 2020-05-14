#include "StringFunction.h"
#pragma once

string powerOf2(int n)
{
	//A unsigned int is 32 bit. We need to determine how many int element we need
	int binaryLength = n / 32 + 1;
	//2^(29*n) requires n int element to display data.
	//Because 2^29 is a number with 9 character and an int can display only 10 character at most
	int decimalLength = n / 29 + 1;

	//Binary Array use for computing
	uint* binaryArr = new uint[binaryLength];

	//Decimal Array use for storing result
	uint* decimalArr = new uint[decimalLength];

	for (int i = 0; i < binaryLength; i++)
		binaryArr[i] = 0;

	//These are the mostsignificant bit
	binaryArr[binaryLength - 1] = 1 << (n % 32);

	int i = 0;
	while (binaryLength > 0)
	{
		ulong num = 0;
		for (int j = binaryLength - 1; j >= 0; j--)
		{
			num = (num << 32) | binaryArr[j];
			binaryArr[j] = num / 1000000000;
			num %= 1000000000;
		}

		decimalArr[i++] = (uint)num;
		while (binaryLength > 0 && binaryArr[binaryLength - 1] == 0)
			binaryLength--;
	}

	stringstream ss;
	i--;
	ss << decimalArr[i];
	while (i > 0)
	{
		i--;
		ss << setw(9) << setfill('0') << decimalArr[i];
	}

	delete[] binaryArr;
	delete[] decimalArr;
	return ss.str();
}

string divideBy2(string num)
{
	if (num == "1" || num == "0")
		return "0";

	string result;
	char remainder = 0, temp;
	int i = 0;

	if (num[0] == '1')
	{
		remainder = 1;
		i++;
	}

	for (; i < num.length(); i++)
	{
		temp = remainder * 10 + num[i] - '0';
		result.push_back(temp / 2 + +'0');

		//When divided by 2, the remainder can be only 0 or 1.
		//We can use & 1 to determine a number is even or odd.
		//If the number is even, the remainder is 1. Else remainder is 0.
		remainder = temp & 1;
	}
	return result;
}

string addStringNumber(string &a, string &b)
{
	if (a.length() < b.length())
		return addStringNumber(b, a);
	string result = "";

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	char carry = 0;
	int i;
	for (i = 0; i < b.length(); i++)
	{
		char temp = a[i] - '0' + b[i] - '0' + carry;
		result.push_back(temp % 10 + '0');
		carry = temp / 10;
	}

	for (; i < a.length(); i++)
	{
		char temp = a[i] - '0' + carry;
		result.push_back(temp % 10 + '0');
		carry = temp / 10;
	}

	if (carry)
		result.push_back(carry + '0');

	reverse(result.begin(), result.end());

	return result;
}
