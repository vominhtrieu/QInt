#pragma once
#define uint unsigned int
#define ulong unsigned long long
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

//Return a string number which is result of 2^n
string powerOf2(int n);
//Divide a string number by 2. Only work with non-negative number.
string divideBy2(string num);
//Return sum of two positive string number.
string addStringNumber(string &a, string &b);