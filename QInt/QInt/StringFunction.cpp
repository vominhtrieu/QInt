#pragma once
#include "StringFunction.h"

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
