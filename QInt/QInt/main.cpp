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
	cout << "a - b = " << a - b << "\n";
	cout << "a * b = " << a * b << "\n";
	cout << "a / b = " << a / b << "\n";
	cout << "a % b = " << a % b << "\n";

	//if (a < b)
	//	cout << "a < b\n";
	//if (a > b)
	//	cout << "a > b\n";
	//if (a <= b)
	//	cout << "a <= b\n";
	//if (a >= b)
	//	cout << "a >= b\n";
	//if (a == b)
	//	cout << "a == b\n";
	//if (a != b)
	//	cout << "a != b\n";

	//int amount;
	//cout << "Shift/Rotate amount: ";
	//cin >> amount;
	cout << "a = " << a.toBinary() << "\n";
	cout << "b = " << b.toBinary() << "\n";
	//cout << "a <<  " << amount << " = " << (a << amount).toBinary() << "\n";
	//cout << "a >>  " << amount << " = " << (a >> amount).toBinary() << "\n";
	//cout << "a rol " << amount << " = " << (a.rol(amount).toBinary()) << "\n";
	//cout << "a ror " << amount << " = " << (a.ror(amount).toBinary()) << "\n";

	//cout << "a & b = " << (a & b).toBinary() << "\n";
	//cout << "a | b = " << (a | b).toBinary() << "\n";
	//cout << "a ^ b = " << (a ^ b).toBinary() << "\n";
	//cout << "~a = " << (~a).toBinary() << "\n";

	return 0;
}