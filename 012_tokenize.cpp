/*
 * 012_tokenize.cpp
 *
 */
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<memory>
using namespace std;

// a function object
struct trimmer
{
	const string avoid;
	trimmer(const string &avoid) : avoid { avoid } { }
	string &operator()(string &s) const noexcept
	{
		size_t n = 0;
		if (!s.empty() && !avoid.empty())
		{
			(n = s.find_first_not_of(avoid)) == string::npos ? s.erase() : s.erase(0, n);
			(n = s.find_last_not_of (avoid)) == string::npos ? s.erase() : s.erase(n + 1);
		}
		return s;
	}
};

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
	char buf[256];

	// C-String with test data
	const char *data = "Monday;Tuesday;\n\n;Wednesday;Thursday;Friday; ;Saturday;;;;Sunday;;";

	// remove whitespace
	struct trimmer trm(" \r\n");

	istringstream stm(data); // using a stream for parsing the data

	vector<string> toks;

	while (!stm.eof())
	{
		stm.getline(buf, sizeof(buf), ';');
		unique_ptr<string> s = unique_ptr<string>(new string(buf));
		trm(*s);
		toks.push_back(*s);
	}

	// remove empty strings
	auto new_end = remove_if(toks.begin(), toks.end(), [](string &s) { return s.empty(); });

	for (auto i = toks.begin(); i != new_end; i++)
		cout << "'" << *i << "'" << '\n';

	return 0;
}
