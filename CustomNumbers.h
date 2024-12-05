#pragma once

#ifndef CUSTOM_NUMBERS
#define CUSTOM_NUMBERS

#include <string>
#include <iostream>
#include <algorithm>

typedef std::basic_string<unsigned char> string;

unsigned char uc(char);//to unsigned char
string to_str(char);
string to_str(std::string);
void to_computable(string*);
short int multiply(unsigned char, string*, short int);
string multiplyBase10(string*, string*);
string divideBase10(string*, int);
string divideBase10(string*, int, int*);
string powerOfBase10Number(unsigned char, short int);
string sumOfBase10Numbers(string*, string*);
string base254to10(string*);
//0000 0000
//254: from 2 to 255 inclusive
void toBase10(string*, short int);

class custom_numbers
{
private:
	string main;
	short int base; //default is 10
	bool isSingleNr = false;
	unsigned char separator;
	short int length; //number of numbers in it, if only 1 number in it, then this will always be 1


	void findSep() {
		switch (base)
		{
		case 10:
			separator = 32;
			break;
		case 254:
			separator = 1;
			break;
		case 255:
			separator = 0;
			break;
		case 256:
			length = 1; return;
			break;
		default:
			separator = 32;
			break;
		}
	}
	void findnSetLength() {
		if (main.empty()) { length = 0; return; }
		short int l = 0;
		for (unsigned char& ch : main) if (ch == separator) l++;
		if (l == 0) {
			length = 1;
			return;
		}
		length = l + 1;
		return;
	}
public:
	custom_numbers() { length = 0; base = 10;  this->findSep();}
	custom_numbers(string* nr) { main = *nr; base = 10; this->findSep(); this->findnSetLength(); }
	custom_numbers(string* nr, short int b) { main = *nr; base = b; this->findSep(); this->findnSetLength(); isSingleNr = (base == 256); }
	custom_numbers(short int b) { length = 0; base = b; this->findSep(); isSingleNr = (base == 256); }
	custom_numbers(string* nr, short int l, short int b) { main = *nr; length = l; base = b; this->findSep(); isSingleNr = (base == 256); }

	custom_numbers& operator=(const string* newNr) {
		main = *newNr;
		this->findnSetLength();
		return *this;
	}
	custom_numbers& operator=(string* newNr) {
		main = *newNr;
		this->findnSetLength();
		return *this;
	}
	custom_numbers& operator=(const string newNr) {
		main = newNr;
		this->findnSetLength();
		return *this;
	}
	custom_numbers& operator=(const custom_numbers& cnr) {
		if (this != &cnr) {
			main = cnr.main;
			base = cnr.base;
			isSingleNr = cnr.isSingleNr;
			separator = cnr.separator;
			length = cnr.length;
		}
		return *this;
	}

	void SetIsSingleNr(bool sn) {
		isSingleNr = sn;
	}
	void SetLength(short int nl) {
		length = nl;
	}
	void print() {
		for (unsigned char& ch : main) std::cout << ch;
		std::cout << " | " << length;
	}
	void setSep(unsigned char s) {
		separator = s;
	}
	string getNumber(short int nrIndex) { //Only usable for multiple numbers
		short int currNr = 0, start = -1;
		size_t l = -1;
		size_t strSize = main.length();
		bool isTheNr = false;
		for (int i = 0; i < strSize; i++) {
			if (!isTheNr && currNr == nrIndex) {
				start = i;
				isTheNr = true;
			}
			if (main[i] == separator) { if (isTheNr) { l = i - start; break; } else currNr++; }
		}
		if (l == -1) l = strSize;
		return main.substr(start, l);
	}
	short int getSetLength() {
		findnSetLength();
		return length;
	}
};

#endif

//TO DO:
//		-toBase10 Function
//		-toBase16 Function
//		-toBase64 Function
//		-toBase254 Function
//		-toBase255 Function
//		-toBase256 Function
//		ALL OF THE ABOVE TO BE MADE GLOBAL
//		==================================
//		-getMainNr()
//		-unsigned char getBase()   ---- returns an unsigned char with only 1 bit set representing it's base
//		-short int base -> unsigned char base
//		-operator overloading for +, -, /, *, +=, -=, *=, /= (if only modifying the root operation isn't enough)
//		- 