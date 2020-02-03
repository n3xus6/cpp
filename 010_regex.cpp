/*
 * 010_regex.cpp
 * 2018-02-18
 *
 * A current C++ library is needed to run this example.
 * GCC 5 works. To make it run without valgrind errors
 * use GCC 7.
 */
#include<iostream>
#include<string>
#include<regex>
#include<cstring>
using namespace std;

int main()
{
	// Raw string literal
	string raw = R"(\x31\x32\x33)";
	string lit = "\x31\x32\x33";

	cout << raw << endl << lit << endl;

	// Get all words that start with letter 't'
	string s = "The quick brown fox jumps over the lazy dog";
	regex r(R"(([T])(\w+))", regex::icase);

	for (sregex_iterator it(s.begin(), s.end(), r); it != sregex_iterator{}; it++)
	{
		smatch sm = *it;
		cout << sm[0] << endl; // full match
		cout << sm[1] << endl; // first letter (1. subexpression)
		cout << sm[2] << endl; // remaining letters (2. subexpression)
	}

	// Get the position of the words that start with 't'
	smatch sm;
	string s2 = s;
	smatch::difference_type offset = 0;
	while (regex_search(s2, sm, r) == true)
	{
		cout << "pos: " << sm.position() + offset << endl;
		offset += sm.position() + sm.length();
		s2 = sm.suffix();
	}

	// Get the tokens between the words that start with letter 't'...
	for (sregex_token_iterator it(s.begin(), s.end(), r, -1); it != sregex_token_iterator{}; it++)
	{
		ssub_match ssm = *it;
		cout << "'" << ssm << "'" << endl;
	}

	// Check if the regular expression 'r' matches the entire string 's'
	s = "1337coffeebreak(-_-)";
	r = "([[:d:]]+)?([[:w:]]+)?([[:d:]]+)?([[:punct:]]+)?";

	if (regex_match(s, sm, r))
	{
		for (smatch::size_type i = 1; i < sm.size(); i++)
		{
			cout << i << ": ";
			if (sm[i].matched)
				cout << sm[i];
			cout << endl;
		}
	}

	// Find matches in a C-String
	const char *cstr = "echo -e -n foobar";
	r = R"(echo|\w+r)";
	for (cregex_iterator it(cstr, cstr + strlen(cstr), r); it != cregex_iterator(); it++)
	{
		cout << (*it).str() << endl;
	}
}
