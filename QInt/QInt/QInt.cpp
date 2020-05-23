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
	char otherElementValue = (n >> 31) ? (-1) : 0;
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
	QInt result = *this;

	return result + (-other);
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
	//throw exception id other == 0
	if (other == 0)
		throw "Division by zero";

	//Restoring Division Algorithm
	QInt result = *this;
	QInt remainder;

	char signBitA = result.getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);

	if (signBitA && signBitB)
		return (-*this) / (-other);
	if (signBitA)
		return -((-*this) / other);
	if (signBitB)
		return -(*this / -other);

	if (result < other)
		return QInt();

	remainder = signBitA ? -1 : 0;
	int k = MaxBitIndex;
	while (k >= 0)
	{
		remainder = remainder << 1;
		remainder.setBit(0, result.getBit(MaxBitIndex));
		result = result << 1;
		remainder = remainder - other;

		if (remainder.getBit(MaxBitIndex))
		{
			result.setBit(0, 0);
			remainder = remainder + other;
		}
		else
			result.setBit(0, 1);

		k -= 1;
	}
	//if (signBitA || signBitB)
	//	result = -result;

	return result;
}

QInt QInt::operator % (QInt other) const
{
	//throw exception id other == 0
	if (other == 0)
		throw "Division by zero";

	//Restoring Division Algorithm
	QInt result = *this;
	QInt remainder;

	char signBitA = result.getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);

	if (signBitA && signBitB)
		return -((-*this) % (-other));
	if (signBitA)
		return -((-*this) % other);
	if (signBitB)
		return (*this % -other);

	if (result < other)
		return result;

	remainder = signBitA ? -1 : 0;
	int k = MaxBitIndex;
	while (k >= 0)
	{
		remainder = remainder << 1;
		remainder.setBit(0, result.getBit(MaxBitIndex));
		result = result << 1;
		remainder = remainder - other;

		if (remainder.getBit(MaxBitIndex))
		{
			result.setBit(0, 0);
			remainder = remainder + other;
		}
		else
			result.setBit(0, 1);

		k -= 1;
	}

	return remainder;
}

QInt QInt::operator-() const
{
	QInt temp = *this;

	for (int i = 0; i < DataSize; i++)
	{
		temp.data[i] = ~data[i];
	}

	temp = temp + (QInt)1;
	return temp;
}

QInt QInt::operator&(QInt other) const
{
	QInt result = *this;
	for (int i = 0; i < DataSize; i++)
	{
		result.data[i] &= other.data[i];
	}
	return result;
}

QInt QInt::operator|(QInt other) const
{
	QInt result = *this;
	for (int i = 0; i < DataSize; i++)
	{
		result.data[i] |= other.data[i];
	}
	return result;
}

QInt QInt::operator^(QInt other) const
{
	QInt result = *this;
	for (int i = 0; i < DataSize; i++)
	{
		result.data[i] ^= other.data[i];
	}
	return result;
}

QInt QInt::operator~() const
{
	QInt result = *this;
	for (int i = 0; i < DataSize; i++)
	{
		result.data[i] = ~result.data[i];
	}
	return result;
}

QInt QInt::operator<<(int amount) const
{
	if (amount > MaxBitIndex)
		return 0;
	QInt result = *this;

	for (int a = 0; a < amount; a += 31)
	{
		int tempAmount = (amount - a) > 31 ? 31 : amount - a;

		for (int i = 0; i <= MaxArrayIndex; i++)
		{
			result.data[i] <<= tempAmount;

			if (i < MaxArrayIndex)
			{
				result.data[i] |= (result.data[i + 1] >> (32 - tempAmount));
			}
		}
	}

	return result;
}

QInt QInt::operator>>(int amount) const
{
	if (amount > MaxBitIndex)
		return ~0;
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

QInt QInt::rol(int amount) const
{
	QInt result = *this;

	for (int a = 0; a < amount; a += 31)
	{
		int tempAmount = (amount - a) > 31 ? 31 : amount - a;
		uint tempData = result.data[0];
		for (int i = 0; i <= MaxArrayIndex; i++)
		{
			result.data[i] <<= tempAmount;

			if (i < MaxArrayIndex)
				result.data[i] |= (result.data[i + 1] >> (32 - tempAmount));
			else
				result.data[i] |= (tempData >> (32 - tempAmount));
		}
	}

	return result;
}

QInt QInt::ror(int amount) const
{
	QInt result = *this;

	for (int a = 0; a < amount; a += 31)
	{
		int tempAmount = (amount - a) > 31 ? 31 : amount - a;
		int tempData = result.data[MaxArrayIndex];
		for (int i = MaxArrayIndex; i >= 0; i--)
		{
			result.data[i] >>= tempAmount;
			if (i > 0)
				result.data[i] |= (result.data[i - 1] << (32 - tempAmount));
			else
				result.data[i] |= (tempData << (32 - tempAmount));
		}
	}

	return result;
}

int QInt::compare(QInt other) const
{
	for (int i = 0; i < DataSize; i++)
	{
		if (this->data[i] > other.data[i])
			return 1;
		if (this->data[i] < other.data[i])
			return -1;
	}
	return 0;
}

bool QInt::operator>(QInt other) const
{
	char signBitA = this->getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);
	if (signBitA && !signBitB)
		return false;
	if (!signBitA && signBitB)
		return true;
	return (*this).compare(other) == 1;
}

bool QInt::operator<(QInt other) const
{
	char signBitA = this->getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);
	if (signBitA && !signBitB)
		return true;
	if (!signBitA && signBitB)
		return false;
	return (*this).compare(other) == -1;
}

bool QInt::operator>=(QInt other) const
{
	char signBitA = this->getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);
	if (signBitA && !signBitB)
		return false;
	if (!signBitA && signBitB)
		return true;
	return (*this).compare(other) != -1;
}

bool QInt::operator<=(QInt other) const
{
	char signBitA = this->getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);
	if (signBitA && !signBitB)
		return true;
	if (!signBitA && signBitB)
		return false;
	return (*this).compare(other) != 1;
}

bool QInt::operator==(QInt other) const
{
	for (int i = 0; i < DataSize; i++)
	{
		if (this->data[i] != other.data[i])
			return false;
	}

	return true;
}

bool QInt::operator!=(QInt other) const
{
	for (int i = 0; i < DataSize; i++)
	{
		if (this->data[i] != other.data[i])
			return true;
	}

	return false;
}

QInt& QInt::operator=(QInt other)
{
	for (int i = 0; i < DataSize; i++)
	{
		this->data[i] = other.data[i];
	}
	return *this;
}

QInt& QInt::operator=(int other)
{
	data[MaxArrayIndex] = other;
	char otherElementValue = (other >> 31) ? (~0) : 0;
	for (int i = 0; i < MaxArrayIndex; i++)
	{
		data[i] = otherElementValue;
	}
	return (*this);
}

string QInt::toBinary() const
{
	string result = "";
	for (int i = MaxBitIndex; i >= 0; i--)
	{
		result.push_back(getBit(i) + '0');
	}
	uint first = result.find_first_not_of('0');
	if (first > MaxBitIndex)
		return "0";
	return result.substr(first);
}

string QInt::toDec() const
{
	QInt temp = getBit(MaxBitIndex) ? (-(*this)) : (*this);

	vector<int> resultArr;
	while (temp > 0)
	{
		resultArr.push_back((temp % 1000000000).toInt());
		temp = temp / 1000000000;
	}

	stringstream ss;

	if (resultArr.size() == 0)
		return "0";
	ss << resultArr[resultArr.size() - 1];

	for (int i = resultArr.size() - 2; i >= 0; i--)
	{
		ss << setw(9) << setfill('0') << resultArr[i];
	}

	if (getBit(MaxBitIndex))
		return "-" + ss.str();
	return ss.str();
}

string QInt::toHex() const
{
	string result = "";

	QInt temp = *this;

	int k = MaxBitIndex;
	while (k > 0)
	{
		k -= 4;
		uint num = (temp >> (MaxBitIndex - 3)).data[MaxArrayIndex] & 15;
		char ch;
		
		if (num < 10)
			ch = num + '0';
		else
			ch = num + 'A' - 10;

		result.push_back(ch);
		temp = temp << 4;
	}

	uint first = result.find_first_not_of('0');
	if (first >= MaxBitIndex)
		return "0";

	result = result.substr(first);

	return result;
}

void QInt::fromBinary(string bin)
{
	*this = QInt();
	
	int bitIndex = 0;

	for (int i = bin.length() - 1; i >= 0; i--)
	{
		if (bin[i] == '1')
			setBit(bitIndex, 1);
		bitIndex++;
	}

	if (bin[0] == '1')
	{
		while (bitIndex >= MaxBitIndex)
		{
			setBit(bitIndex++, 1);
		}
	}
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
	QInt result;

	hex.erase(0, hex.find_first_not_of('0'));

	int hexIndex = 0;
	while (hexIndex < hex.length())
	{
		uint bits;
		if (hex[hexIndex] >= '0' && hex[hexIndex] <= '9')
			bits = hex[hexIndex] - '0';
		else
			bits = hex[hexIndex] - 'A' + 10;
				
		result.data[MaxArrayIndex] |= bits;
		if (hexIndex < hex.length() - 1)
			result = result << 4;

		hexIndex++;
	}

	(*this) = result;
}

int QInt::toInt()
{
	return data[MaxArrayIndex];
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
