#include <sstream>
#include "CommandLineArguments.h"

int main(int argc, char* argv[])
{
	//if (argc != 3)
	//	return 0;

	////argv[0] executable file name, argv[1] input file name, argv[2] output file name
	//ifstream inputFile(argv[1]);
	//ofstream outputFile(argv[2]);
	//if (!inputFile || !outputFile)
	//	return 0;

	//string tempLine;
	//string tempArg;
	//while (!inputFile.eof())
	//{
	//	try
	//	{
	//		getline(inputFile, tempLine);
	//		vector<string> arguments;
	//		stringstream ss(tempLine);
	//		while (ss >> tempArg)
	//		{
	//			arguments.push_back(tempArg);
	//		}
	//		handleArgument(outputFile, arguments);
	//	}
	//	catch (...)
	//	{
	//		outputFile << "\n";
	//	}
	//}

	//inputFile.close();
	//outputFile.close();

	//return 0;

	QInt a;
	/*cout << "a: ";
	cin >> a;*/
	a.fromHex("0127F4D6EC0FFA4601");
	cout << "a: " << a << "\n";

	a = a << 41;
	cout << "a: " << a << "\n";

	cout << a.toHex() << "\n";
	QInt b;
	b.fromHex(a.toHex());
	cout << "b: " << b << "\n";

}