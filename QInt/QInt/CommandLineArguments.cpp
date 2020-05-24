#include "CommandLineArguments.h"

void handleBinaryOperator(ofstream& outputFile, vector<string>& arguments)
{
	string base = arguments[0];

	QInt a, b, result;
	//Read number in specific base
	if (base == "2")
	{
		a.fromBinary(arguments[1]);
		b.fromBinary(arguments[3]);
	}
	else if (base == "10")
	{
		a.fromDec(arguments[1]);
		b.fromDec(arguments[3]);
	}
	else if (base == "16")
	{
		a.fromHex(arguments[1]);
		b.fromHex(arguments[3]);
	}
	else
		return;

	try {
		//Perform operation
		switch (arguments[2][0])
		{
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			result = a / b;
			break;
		case '&':
			result = a & b;
			break;
		case '|':
			result = a | b;
			break;
		case '^':
			result = a ^ b;
			break;
			// Operator left shift <<
		case '<':
			result = a << stoi(arguments[3]);
			break;
			// Operator right shift >>
		case '>':
			result = a >> stoi(arguments[3]);
			break;
		default:
			break;
		}
	}
	catch (...)
	{
		return;
	}

	//Output to file in specific base
	if (base == "2")
		outputFile << result.toBinary();
	else if (base == "10")
		outputFile << result.toDec();
	else if  (base =="16")
		outputFile << result.toHex();
}

void handleUnaryOperator(ofstream& outputFile, vector<string>& arguments)
{
	QInt num, result;

	string base = arguments[0];
	string op = arguments[1];

	//Read number in specific base
	if (base == "2")
		num.fromBinary(arguments[2]);
	else if (base == "10")
		num.fromDec(arguments[2]);
	else if (base == "16")
		num.fromHex(arguments[2]);
	else
		return;

	//Perform operation
	if (op == "~")
		result = ~num;
	else if (op == "rol")
		result = num.rol(1);
	else if (op == "ror")
		result = num.ror(1);
	else
		return;

	//Output to file in specific base
	if (base == "2")
		outputFile << result.toBinary();
	else if (base == "10")
		outputFile << result.toDec();
	else if (base == "16")
		outputFile << result.toHex();
}

void handleBaseConvertingOperator(ofstream& outputFile, vector<string>& arguments)
{
	QInt num;

	//Read number in specific base (arguments[0]
	if(arguments[0] == "2")
		num.fromBinary(arguments[2]);
	else if(arguments[0] == "10")
		num.fromDec(arguments[2]);
	else if(arguments[0] == "16")
		num.fromHex(arguments[2]);
	else
		return;

	//Output to file in specific base
	if (arguments[1] == "2")
		outputFile << num.toBinary();
	else if (arguments[1] == "10")
		outputFile << num.toDec();
	else if (arguments[1] == "16")
		outputFile << num.toHex();
}

void handleArgument(ofstream& outputFile, vector<string>& arguments)
{
	if (arguments.size() == 4)
		handleBinaryOperator(outputFile, arguments);
	else if (arguments.size() == 3)
	{
		if (arguments[1] == "2" || arguments[1] == "10" || arguments[1] == "16")
			handleBaseConvertingOperator(outputFile, arguments);
		else
			handleUnaryOperator(outputFile, arguments);
	}
}