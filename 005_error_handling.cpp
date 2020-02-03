//
// File name: 005_error_handling.cpp
// Date: 2017-10-28
//
#include <iostream>
#include <string>
#include <stdexcept>
using std::cout;
using std::endl;

// Namespace example
namespace foo
{
	void hello() { cout << "Hello from foo.\n"; }
}

namespace bar
{
	void hello() { cout << "Hello from bar.\n"; }
}

// functions throwing pointers and objects
void throw_invalid_argument_value()
{
	throw std::invalid_argument("invalid argument\n");
}

void throw_invalid_argument_pointer()
{
	throw new std::invalid_argument("invalid argument\n");
}

void throw_out_of_range()
{
	throw std::out_of_range { std::string("out of range\n") };
}

void func()
{
	try
	{
		throw_out_of_range();
	}
	catch (std::out_of_range &e)
	{
		cout << e.what();
		throw; // trigger exception again
	}
}

void d() { throw std::length_error("length error\n"); }
void c() { d(); }
void b() { c(); }
void a() { b(); }

int main()
{
	foo::hello();
	bar::hello();

	try
	{
		throw_invalid_argument_pointer();
	}
	catch (std::invalid_argument *e)
	{
		cout << e->what();
		delete e;
	}

	try
	{
		throw_invalid_argument_value();
	}
	catch (std::invalid_argument &e)
	{
		cout << e.what();
	}

	try
	{
		func();
	}
	catch (std::out_of_range&)
	{
		cout << "main(): out of range\n";
	}

	try
	{
		a(); // -> b() -> c() -> d() -> throw ...
	}
	catch (std::exception &e)
	{
		cout << e.what();
	}

	// Compile time checks
	constexpr size_t int_size = sizeof(int);
	constexpr size_t char_size = sizeof(char);
	constexpr size_t long_size = sizeof(long);
	constexpr size_t short_size = sizeof(short);
	constexpr size_t longlong_size = sizeof(long long);
	constexpr size_t long_double_size = sizeof(long double);

	cout << int_size << endl; // 4
	cout << char_size << endl; // 1
	cout << long_size << endl; // 4
	cout << short_size << endl; // 2
	cout << longlong_size << endl; // 8
	cout << long_double_size << endl; // 12

	static_assert(int_size         >= 4,  "size of int < 4!");
	static_assert(char_size        == 1,  "size of int != 1!");
	static_assert(long_size        >= 4,  "size of long < 4!");
	static_assert(short_size       >= 2,  "size of short < 2!");
	static_assert(longlong_size    >= 8,  "size of long long < 8!");
	static_assert(long_double_size >= 12, "size of long long < 12!");
}
