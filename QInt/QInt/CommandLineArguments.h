#pragma once
#include <fstream>
#include <vector>
#include "QInt.h"
using namespace std;

//Handle binary operator and write output to outputFile
void handleBinaryOperator(ofstream& outputFile, vector<string>& arguments);
//Handle unary operator and write output to outputFile
void handleUnaryOperator(ofstream& outputFile, vector<string>& arguments);
//Convert number in arguments[2] from base arguments[0] to base arguments[1]
void handleBaseConvertingOperator(ofstream& outputFile, vector<string>& arguments);
//Read arguments and choose which function need to be called.
void handleArgument(ofstream& outputFile, vector<string>& arguments);