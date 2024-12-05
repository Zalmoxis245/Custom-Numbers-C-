#include "CustomNumbers.h"

unsigned char uc(char x) { return x; };
string to_str(char x) { string a; a.push_back(x); return a; }
string to_str(std::string x) { string a(x.begin(), x.end()); return a; }
void to_computable(string* x) { for (unsigned char& ch : *x) ch -= 48; }
short int multiply(unsigned char x, string* nr, short int nr_len) {
	int carry = 0;
	for (short int i = 0; i < nr_len; i++) {
		int prod = nr->at(i) * x + carry;
		nr->at(i) = prod % 10;
		carry = prod / 10;
	}
	while (carry) {
		nr->push_back(carry % 10);
		carry = carry / 10;
		nr_len++;
	}
	return nr_len;
}
string multiplyBase10(string* a, string* b) {
	if (a->empty() || b->empty()) return to_str(0);
	short int li1 = a->length()-1;
	short int li2 = b->length() - 1;
	int carry = 0;
	string prod;
	for (short int i = 0; i <= li1 + li2 || carry; i++) {
		for (short int j = std::max(0, i - li2); j <= std::min(i, li1); j++)
			carry += a->at(li1 - j) * b->at(li2 - i + j);
		prod.push_back(carry % 10);
		carry /= 10;
	}
	std::reverse(prod.begin(), prod.end());
	return prod;
}
string divideBase10(string* nr, int d) {
	string res;

	int idx = 0;
	int temp = nr->at(idx);
	while (idx < (nr->size() - 1) && temp < d)
		temp = temp * 10 + nr->at(++idx);
	while ((nr->size() - 1) > idx)
	{
		res.push_back(temp / d);
		temp = (temp % d) * 10 + nr->at(++idx);
	}

	res.push_back(temp / d);
	if (res.empty()) return to_str(0);
	return res;
}
string divideBase10(string* nr, int d, int* rest) {
	string res;

	int idx = 0;
	int temp = nr->at(idx);
	while (idx < (nr->size() - 1) && temp < d)
		temp = temp * 10 + nr->at(++idx);
	while ((nr->size() - 1) > idx)
	{
		res.push_back(temp / d);
		temp = (temp % d) * 10 + nr->at(++idx);
	}

	res.push_back(temp / d);
	*rest = temp % d;
	if (res.empty()) return to_str(0);
	return res;
}
//e - exponent
string powerOfBase10Number(unsigned char x, short int e) {
	if (e == 0) return to_str(1);
	string toReturn;
	short int str_len = 0;
	unsigned char temp = x;

	while (temp != 0)
	{
		toReturn.push_back(temp % 10);
		str_len++;
		temp = temp / 10;
	}

	for (short int i = 2; i <= e; i++) str_len = multiply(x, &toReturn, str_len);
	std::reverse(toReturn.begin(), toReturn.end());
	return toReturn;
}

string sumOfBase10Numbers(string* a, string* b) {
	if (a->length() > b->length()) std::swap(a, b);
	string sum;
	short int len1 = a->length();
	short int len2 = b->length();
	short int lenDiff = len2 - len1;
	short int carry = 0;
	int intSum;
	for (int i = len1 - 1; i >= 0; i--) {
		intSum = (a->at(i) + b->at(i + lenDiff) + carry);
		sum.push_back(intSum % 10);
		carry = intSum / 10;
	}
	for (int i = lenDiff - 1; i >= 0; i--) {
		intSum = (b->at(i) + carry);
		sum.push_back(intSum % 10);
		carry = intSum / 10;
	}
	if (carry) sum.push_back(carry);
	std::reverse(sum.begin(), sum.end());
	return sum;
}

string base254to10(string* nr) {

	if (nr->empty()) return to_str('0');

	string toReturn = to_str('\0');;
	unsigned char temp;
	short int currentIndex = 0;
	string currentValue;
	string temp2;
	short int len = nr->length();

	for (short int i = len-1; i >= 0; i--) {
		temp = nr->at(i);
		temp = temp-2;//1111 1101 max; 0000 0000 min
		temp2 = to_str(temp);
		currentValue = powerOfBase10Number(254, currentIndex);
		currentValue = multiplyBase10(&currentValue, &temp2);
		toReturn = sumOfBase10Numbers(&currentValue, &toReturn);
		currentIndex++;
		
		std::cout << "\n";
	}

	return toReturn;

}
void toBase10(string* nr, short int original_base) {
	switch (original_base)
	{
	case 10:
		break;
	case 254:
		base254to10(nr);
		break;
	default:
	
		break;
	}
}

//the number must be pure, without the ASCII +48 overhead and will return pure(obviously)
string base10to254(string* nr) {
	short int len = nr->length();


	return to_str(0);
}