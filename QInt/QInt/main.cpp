#include "QInt.h"

int main(int argc, char* argv[])
{
	QInt a, b;
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	cout << "-a = " << -a << "\n";
	cout << "a + b = " << a + b << "\n";
	cout << "a * b = " << a * b << "\n";

	if (a < b)
		cout << "a < b\n";
	if (a > b)
		cout << "a > b\n";
	if (a <= b)
		cout << "a <= b\n";
	if (a >= b)
		cout << "a >= b\n";
	if (a == b)
		cout << "a == b\n";
	if (a != b)
		cout << "a != b\n";

	/*int amount;
	cout << "amount: ";
	cin >> amount;
	cout << "a << " << amount << " = " << (a << amount) << "\n";*/
	//cout << "b >> 1 = " << (b >> 0) << "\n";/

	return 0;
}