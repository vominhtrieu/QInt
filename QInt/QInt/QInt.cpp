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
	bool isZero = true;
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
	if ((this->getBit(MaxBitIndex) && other.getBit(MaxBitIndex) && !result.getBit(MaxBitIndex))
		|| (!this->getBit(MaxBitIndex) && !other.getBit(MaxBitIndex) && result.getBit(MaxBitIndex)))
		throw "Overflow";
	return result;
}

QInt QInt::operator-(QInt other) const
{
	QInt result = *this;

	return result + (-other);
}

QInt QInt::operator*(QInt other) const
{
	//Fix problem when MIN * 1
	if (other == 1)
		return *this;
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


	if (Q.getBit(MaxBitIndex))
	{
		if (A != -1 || this->getBit(MaxBitIndex) == other.getBit(MaxBitIndex))
			throw "Overflow";
	}
	else
	{
		if (A != 0)
			throw "Overflow";
	}

	return Q;
}

QInt QInt::divide(QInt other, QInt& remainder)
{
	//Throw exception if other == 0
	if (other == 0)
		throw "Division by zero";

	//Restoring Division Algorithm
	QInt result = *this;
	remainder = 0;

	char signBitA = result.getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);

	bool resultSign = signBitA ^ signBitB;

	QInt minNumber;
	minNumber.setBit(MaxBitIndex, 1);
	if (*this == minNumber)
	{
		if (other == -1)
			throw "Overflow";
		else if (other == 1)
			return *this;
	}
	else if (signBitA)
		result = -*this;
	if (signBitB && (other) != minNumber)
		other = -other;

	char compareResult = result.compare(other);

	if (compareResult == -1)
	{
		remainder = *this;
		return 0;
	}
	else if (compareResult == 0)
	{
		return resultSign ? -1 : 1;
	}

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

	if (signBitA)
		remainder = -remainder;

	return resultSign ? -result : result;
}

QInt QInt::operator/(QInt other) const
{
	//Throw exception if other == 0
	if (other == 0)
		throw "Division by zero";

	//Restoring Division Algorithm
	QInt result = *this;
	QInt remainder;

	char signBitA = result.getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);

	bool resultSign = signBitA ^ signBitB;

	QInt minNumber;
	minNumber.setBit(MaxBitIndex, 1);

	if (*this == minNumber)
	{
		if (other == -1)
			throw "Overflow";
		else if (other == 1)
			return *this;
	}
	else if (signBitA)
		result = -*this;
	if (signBitB && (other) != minNumber)
		other = -other;

	char compareResult = result.compare(other);
	if (compareResult == -1)
		return 0;
	else if (compareResult == 0)
		return resultSign ? -1 : 1;

	int k = MaxBitIndex;
	while (k >= 0)
	{
		//shift left [A, Q]
		remainder = remainder << 1;
		remainder.setBit(0, result.getBit(MaxBitIndex));
		result = result << 1;
		//A = A - M
		remainder = remainder - other;

		if (remainder.getBit(MaxBitIndex))
		{
			result.setBit(0, 0);
			remainder = remainder + other;  //restore
		}
		else
			result.setBit(0, 1);

		k -= 1;
	}

	return resultSign ? -result : result;
}

QInt QInt::operator % (QInt other) const
{
	//Throw exception if other == 0
	if (other == 0)
		throw "Division by zero";

	//Also use Restoring Division Algorithm, but return A
	QInt result = *this; //Q
	QInt remainder; //A

	char signBitA = result.getBit(MaxBitIndex);
	char signBitB = other.getBit(MaxBitIndex);

	QInt minNumber;
	minNumber.setBit(MaxBitIndex, 1);

	if (signBitA && (*this) != minNumber)
		result = -*this;
	if (signBitB && (other) != minNumber)
		other = -other;

	char compareResult = result.compare(other);

	if (compareResult == -1)
		return (*this);
	else if (compareResult == 0)
		return 0;

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

	return signBitA ? -remainder : remainder;
}

QInt QInt::operator-() const
{
	return ~(*this) + 1;
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
		return this->getBit(MaxBitIndex) ? -1 : 0;
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
		uint tempData = result.data[MaxArrayIndex];
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
	char otherElementValue = (other >> 31) ? -1 : 0;
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
	bool isNegative = this->getBit(MaxBitIndex);
	QInt temp = *this;
	QInt remainder;

	vector<int> resultArr;
	while (temp != 0)
	{
		//Use both / and % in one statement will give better performance
		temp = temp.divide(1000000000, remainder);
		resultArr.push_back(remainder.toInt());
	}

	stringstream ss;

	if (resultArr.size() == 0)
		return "0";
	ss << resultArr[resultArr.size() - 1];

	for (int i = resultArr.size() - 2; i >= 0; i--)
	{
		ss << setw(9) << setfill('0') << (isNegative ? -resultArr[i] : resultArr[i]);
	}

	return ss.str();
}

string QInt::toHex() const
{
	string result = "";

	QInt temp = *this;

	int k = MaxBitIndex;
	int shiftAmount = MaxBitIndex - 3;
	while (k > 0)
	{
		k -= 4;
		uint num = (temp >> shiftAmount).data[MaxArrayIndex] & 15;
		char ch;

		if (num < 10)
			ch = num + '0';
		else
			ch = num + 55; //55 is ascii value of 'A' - 10

		result.push_back(ch);
		temp = temp << 4;
	}

	uint first = result.find_first_not_of('0');
	if (first >= MaxBitIndex)
		return "0";

	result = result.substr(first);

	return result;
}

int QInt::toInt()
{
	return data[MaxArrayIndex];
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
		//dec[dec.length() - 1] & 1 tell whether dec is even or not, if even remainder is 0 so bit is 0 and vice-versal
		result.setBit(bitIndex++, dec[dec.length() - 1] & 1);
		dec = divideBy2(dec);
	}
	QInt min;
	min.setBit(MaxBitIndex, 1);

	if (isNegative && result != min)
		result = -result;
	(*this) = result;
}

void QInt::fromHex(string hex)
{
	hex.erase(0, hex.find_first_not_of('0'));

	int hexIndex = 0;
	int maxHexIndex = hex.length() - 1;
	uint bits;

	while (hexIndex < hex.length())
	{
		if (hex[hexIndex] >= '0' && hex[hexIndex] <= '9')
			bits = hex[hexIndex] - '0';
		else
			bits = hex[hexIndex] - 55; //55 is ascii value of 'A' - 10

		this->data[MaxArrayIndex] |= bits;
		if (hexIndex < maxHexIndex)
			*this = (*this) << 4;
		hexIndex++;
	}
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
