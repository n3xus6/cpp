//
// File name: 009_string.cpp
// Date: 2017-12-16
//
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;

static string quote()
{
	// string concatenation and returning
	std::string std_str = "?he strength of ";
	char c_str[] = " is that XXX will not XXX believe in him";
	return std_str + "the " + c_str + 'T';
}

int main()
{
	string q = quote();

	// fix the quote using string operations
	q.replace(29, 3, "people");
	q.insert(20, "vampire");
	q.erase(52, 4);
	q.front() = q.back();
	q.pop_back();
	q.push_back('.');

	// print quote
	cout << '"' << q << '"' << endl;

	// print quote as a C string
	printf("\"%s\"\n", q.c_str());

	// print first and last character (at(), [])
	cout << "'" << q.at(0) << "', '" << q[q.length()-1] << "'" << endl;

	// string search operations
	cout << q.find("re") << endl; // first occurrence of "re" (6)
	cout << q.rfind("re") << endl; // last occurrence of "re" (25)
	cout << q.find_first_of("vsp") << endl; // first occurrence of 'v', 's' or 'p' (4)
	cout << q.find_last_of("vsp") << endl; // last occurrence of 'v', 's' or 'p' (57)
	cout << q.find_first_not_of("Tnmihe. ") << endl; // first occurrence not of 'T', 'n', ... (4)
	cout << q.find_last_not_of("Tnmihe. ") << endl; // last occurrence not of 'T', 'n', ... (57)

	// not found
	string search_str = "zombie";
	if (q.find(search_str) == string::npos)
		cout << '"' << search_str << '"' << " not found!" << endl;

	// create substring, print in reverse order
	string sub_str = q.substr(20, 7);
	for (auto it = sub_str.rbegin(); it != sub_str.rend(); it++)
		cout << *it;
	cout << endl;

	// Examples for capacity(), append(), clear(), shrink_to_fit(), reserve() and resize().
	string large_str;
	cout << "capacity: " << large_str.capacity() << endl; // 0 (15) depending on the C++ library implementation

	large_str.append(1001, 'x');
	cout << "capacity: " << large_str.capacity() << endl; // 1001

	large_str.clear();
	cout << "capacity: " << large_str.capacity() << endl; // 1001

	large_str.shrink_to_fit();
	cout << "capacity: " << large_str.capacity() << endl; // 0 (15)

	//
	// Provide the number of characters in front to reduce the number of allocs and
	// the amount of memory occupied in the next loop.
	//
	large_str.reserve(1001);

	for (int i = 0; i != 1001; i++)
		large_str.push_back('x');

	// 1001 when calling reserve(), otherwise 1024 (1920) depending on the C++ library implementation
	cout << "capacity: " << large_str.capacity() << endl;

	large_str.resize(1);       // truncate
	large_str.resize(2, 'y');  // extend
	cout << large_str << endl; // "xy"

	cout << large_str.max_size() << endl; // 2^31 - 1 (2^62 - 7) on my Windows (Linux) system

	// wide character string
	wstring w_str(L"I'm a 'wstring'.");
	wcout << w_str << endl;

	cout << w_str.length() << endl; // 16
	cout << w_str.size() << endl;   // 16 (size means also number of characters)

	// Windows / Codepage 850: print characters up to 0xFF.
	// Linux / Codepage 65001: print characters up to 0x7F.
	for (int i = 32; i != 256; i += 16)
	{
		for (int j = i; j != i + 16; j++)
			wcout << static_cast<wchar_t>(j);
		wcout << endl;
	}
}
