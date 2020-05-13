#include "QInt.h"

QInt::QInt()
{
	for (int i = 0; i < DataSize; i++)
	{
		data[i] = 0;
	}
}

char QInt::getBit(char index)
{
	return (data[(MaxBitIndex - index) / 4] >> (index % 32)) & 1;
}

void QInt::setBit(char index, char value)
{
	if (value)
		data[(MaxBitIndex - index) / 4] |= (1 << (MaxBitIndex - value));
	else
		data[(MaxBitIndex - index) & 4] &= ~(1 << (MaxBitIndex - value));
}

QInt QInt::operator+(QInt other)
{
	return QInt();
}

QInt QInt::operator-(QInt other)
{
	return QInt();
}

QInt QInt::operator*(QInt other)
{
	return QInt();
}

QInt QInt::operator/(QInt other)
{
	return QInt();
}

QInt QInt::operator-()
{
	return QInt();
}

QInt QInt::operator&(QInt other)
{
	return QInt();
}

QInt QInt::operator|(QInt other)
{
	return QInt();
}

QInt QInt::operator^(QInt other)
{
	return QInt();
}

QInt QInt::operator~()
{
	return QInt();
}

QInt QInt::operator<<(int amount)
{
	return QInt();
}

QInt QInt::operator>>(int amount)
{
	return QInt();
}

QInt QInt::rol()
{
	return QInt();
}

QInt QInt::ror()
{
	return QInt();
}

bool QInt::operator>(QInt other)
{
	return false;
}

bool QInt::operator<(QInt other)
{
	return false;
}

bool QInt::operator>=(QInt other)
{
	return false;
}

bool QInt::operator<=(QInt other)
{
	return false;
}

bool QInt::operator==(QInt other)
{
	return false;
}

bool QInt::operator!=(QInt other)
{
	return false;
}

QInt QInt::operator=(QInt other)
{
	return QInt();
}

QInt QInt::operator=(int other)
{
	return QInt();
}

string QInt::toBinary()
{
	return string();
}

string QInt::toDec()
{
	return string();
}

string QInt::toHex()
{
	return string();
}

void QInt::fromBinary(string bin)
{
}

void QInt::fromDec(string dec)
{
}

void QInt::fromHex(string hex)
{
}

ostream& operator<<(ostream& out, const QInt& number)
{
	// TODO: insert return statement here
}

istream& operator>>(ostream& in, QInt& number)
{
	// TODO: insert return statement here
}
