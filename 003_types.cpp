//
// File name: 003_types.cpp
// Date: 2017-09-10
//
#include <iostream>
#include <typeinfo>
using namespace std;

constexpr int mul2(int i) { return i*2; }

void loop1(const char *cstr);
void loop2(const string &str);

int main()
{
	int x = 1;
	int y = { 1 };
	int z { 1 }; // ISO C++ 11 (-std=c++0x)
	auto w = 1;

	cout << "x=" << x << " y=" << y << " z=" << z << " w=" << w << endl;

	// "error: narrowing conversion of '1.0e+0' from 'double' to 'int' inside { } [-Wnarrowing]"
	// int err { 1.0 };

	int no_err = 1.0;

	cout << "no_err=" << no_err << endl;

	int var = 1;
	const int c = 1 + var;

	constexpr int c2 = 1;

	// "error: the value of 'c' is not usable in a constant expression"
	// constexpr int c3 = 1 + c;

	constexpr int c4 = 1 + mul2(c2); // produce compile-time constant (argument is a constexpr value)
	const int c5 = 1 + mul2(var); // produce value at run time

	cout << "var=" << var << " c=" << c << " c2=" << c2 << " c4=" << c4 << " c5=" << c5 << endl;

	char greeting[] = "Hello World!";
	loop1(greeting);

	string greeting2 = "Hello World!";
	loop2(greeting2);

	// ranged-based for loops also work with native arrays...
	for (const auto &chr: greeting)
		if (chr != '\0') // ... but here we have to catch the zero-termination.
			cout << chr;
	cout << endl;
}

void loop1(const char *cstr)
{
	cout << "loop1:" << endl;
	while(*cstr)
		cout << *cstr++;
	cout << endl;
}

void loop2(const string &str)
{
	cout << "loop2:" << endl;
	for (const auto &x: str)
		cout << x;
	cout << endl;
}
