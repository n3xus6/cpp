//
// File name: 002_limits_test.cpp
// Date: 2017-09-10
//
#include <iostream>
using namespace std;

int main()
{
	char ch_var = static_cast<char>(-159);
	cout << ch_var << endl; // 'a' (256 - 159 = 97)

	int i_var = 2147483647;
	cout << i_var << endl << i_var + 1 << endl; // -2147483648

	long long int ll_var = 9223372036854775807;
	cout << ll_var << endl << ll_var + 1 << endl; // -9223372036854775808

	unsigned long long int ull_var = 18446744073709551615LLU;
	cout << ull_var << endl; // 18446744073709551615

	bool b_var = 42;
	cout << static_cast<int>(b_var) << endl; // 1 (the original value is lost)

	float f_var = 0.000000000000000000000000000000000000001;
	cout << f_var << endl; // 1e-039

	double d_var = 0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001;
	cout << d_var << endl; // 1e-317

	double d_var2 = 1e-318;
	cout << d_var2 << endl; // 9.99999e-319

	cout << (true == 1) << endl; // 1

	cout << (false == true-true) << endl; // 1
}
