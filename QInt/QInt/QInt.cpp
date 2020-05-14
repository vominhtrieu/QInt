#include "QInt.h"

QInt::QInt()
{
	for (int i = 0; i < DataSize; i++)
	{
		data[i] = 0;
	}
}

QInt::QInt(int n)
{
	data[MaxArrayIndex] = n;
	char otherElementValue = (n >> 31) ? (~0) : 0;
	for (int i = 0; i < MaxArrayIndex; i++)
	{
		data[i] = otherElementValue;
	}
}

char QInt::getBit(char index) const
{
	return (data[(MaxBitIndex - index) / 32] >> (index % 32)) & 1;
}

void QInt::setBit(char index, char value)
{
	if (value)
		data[(MaxBitIndex - index) / 32] |= (1 << (index % 32));
	else
		data[(MaxBitIndex - index) / 32] &= ~(1 << (index % 32));
}

QInt QInt::operator+(QInt other) const
{
	QInt result;
	uint temp = ~(1 << 31);
	uint carry = 0;

	for (int i = MaxArrayIndex; i >= 0; i--)
	{
		//To use ability of int in c++, we use build-in operator + of int
		//However if there's an overflow in operator next element won'n know it
		//So we add only 31 bits of int, leftMostBit will be first bit of 2 int
		//and result of previous operator
		uint data = (this->data[i] & temp) + (other.data[i] & temp) + carry;
		result.data[i] = data;

		uint leftMostBit = (data >> 31) + (this->data[i] >> 31) + (other.data[i] >> 31);
		result.setBit((MaxArrayIndex - i) * 32 + 31, leftMostBit % 2);
		//If LMB is greater than 1, so there's an overflow, we must set carry to 1
		carry = leftMostBit > 1 ? 1 : 0;
	}

	return result;
}

QInt QInt::operator-(QInt other) const
{
	return QInt();
}

QInt QInt::operator*(QInt other) const
{
	//Booth's algorithm
	QInt A;
	QInt Q = other;
	char Q1 = 0;

	int k = MaxBitIndex;
	while (k >= 0)
	{
		//Q0Q1=10 
		if (Q.getBit(0) && !Q1)
			A = A - (*this);
		//Q0Q1=01
		else if (!Q.getBit(0) && Q1)
			A = A + (*this);

		//Shift right arithmetic [A, Q, Q1]
		Q1 = Q.getBit(0);
		Q = Q >> 1;
		Q.setBit(MaxBitIndex, A.getBit(0));
		A = A >> 1;
		k--;
	}

	return Q;
}

QInt QInt::operator/(QInt other) const
{
	return QInt();
}

QInt QInt::operator-() const
{
	QInt temp = *this;

	for (int i = 0; i < DataSize; i++)
	{
		temp.data[i] = ~data[i];
	}

	temp = temp + 1;
	return temp;
}

QInt QInt::operator&(QInt other) const
{
	return QInt();
}

QInt QInt::operator|(QInt other) const
{
	return QInt();
}

QInt QInt::operator^(QInt other) const
{
	return QInt();
}

QInt QInt::operator~() const
{
	return QInt();
}

QInt QInt::operator<<(int amount) const
{
	return QInt();
}

QInt QInt::operator>>(int amount) const
{
	QInt result = *this;

	for (int a = 0; a < amount; a += 31)
	{
		int tempAmount = (amount - a) > 31 ? 31 : amount - a;

		for (int i = MaxArrayIndex; i >= 0; i--)
		{
			if (i > 0)
			{
				result.data[i] >>= tempAmount;
				result.data[i] |= (result.data[i - 1] << (32 - tempAmount));
			}
			else
			{
				result.data[i] = ((int)result.data[i]) >> tempAmount;
			}
		}
	}

	return result;
}

QInt QInt::rol() const
{
	return QInt();
}

QInt QInt::ror() const
{
	return QInt();
}

bool QInt::operator>(QInt other) const
{
	return false;
}

bool QInt::operator<(QInt other) const
{
	return false;
}

bool QInt::operator>=(QInt other) const
{
	return false;
}

bool QInt::operator<=(QInt other) const
{
	return false;
}

bool QInt::operator==(QInt other) const
{
	return false;
}

bool QInt::operator!=(QInt other) const
{
	return false;
}

QInt QInt::operator=(QInt other)
{
	for (int i = 0; i < DataSize; i++)
	{
		this->data[i] = other.data[i];
	}
	return *this;
}

QInt QInt::operator=(int other)
{
	return QInt();
}

string QInt::toBinary() const
{
	string result = "";
	for (int i = MaxBitIndex; i >= 0; i--)
	{
		result.push_back(getBit(i) + '0');
	}
	return result;
}

string QInt::toDec() const
{
	string result = "0";
	QInt temp = getBit(MaxBitIndex) ? (-(*this)) : (*this);

	for (int i = MaxBitIndex; i >= 0; i--)
	{
		char bit = temp.getBit(i);
		if (bit)
		{
			string p = powerOf2(i);
			result = addStringNumber(result, p);
		}
	}

	if (getBit(MaxBitIndex))
		return "-" + result;
	return result;
}

string QInt::toHex() const
{
	return string();
}

void QInt::fromBinary(string bin)
{
}

void QInt::fromDec(string dec)
{
	bool isNegative = dec[0] == '-';

	QInt result;

	if (isNegative)
		dec.erase(0, 1);
	dec.erase(0, dec.find_first_not_of('0'));

	if (dec == "")
		return;

	int bitIndex = 0;
	while (dec != "0" && bitIndex <= MaxBitIndex)
	{
		result.setBit(bitIndex++, dec[dec.length() - 1] & 1);
		dec = divideBy2(dec);
	}
	if (isNegative)
		result = -result;
	(*this) = result;
}

void QInt::fromHex(string hex)
{
}

ostream& operator<<(ostream& out, const QInt& number)
{
	out << number.toDec();
	return out;
}

istream& operator>>(istream& in, QInt& number)
{
	string s;
	in >> s;
	number.fromDec(s);
	return in;
}
