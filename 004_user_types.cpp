//
// File name: 004_user_types.cpp
// Date: 2017-10-08
//
#include <iostream>
#include <iomanip> // setw, setfill
#include <cstdio> // printf
#include <cstring> // memset
using namespace std;

int main()
{
	unsigned int ivar = (unsigned int) NULL;
	cout << ivar << endl; // 0

	ivar = (unsigned int) nullptr;
	cout << ivar << endl; // 0

	// Print memory address in hex format.
	cout << "0x"
		 << noshowbase
		 << hex
		 << setw(2*sizeof(unsigned int))
		 << setfill('0')
		 << (unsigned int) &ivar
		 << endl;

	cout << showbase << dec << setw(0) << setfill(' '); // undo manipulator settings

	// C code which provides the same result
	printf("%#.8x\n", (unsigned int) &ivar);

	// union example
	union
	{
		char chr; // 1 byte
		int i; // 4 byte
		double d; // 8 byte
	} u;

	cout << sizeof(u) << endl; // 8

	u.chr = '*';
	cout << u.chr << endl;

	u.i = 42;
	cout << u.i << endl;

	u.d = -0.5;
	cout << u.d << endl;

	// enum example
	enum { e1_0, e1_1, e1_2 };

	cout << "e1_0: " << e1_0 << endl << "e1_1: " << e1_1 << endl << "e1_2: " << e1_2 << endl;

	// another enum example
	typedef enum enum1_t { enum1_0, enum1_1, enum1_2 } enum1_type;

	enum enum1_t enum1Var = enum1_2;
	enum1_t enum1Var2 = enum1_2;
	enum1_type enum1Var3 = enum1_2;

	cout << "enum1Var: "  << enum1Var << endl;  // 2
	cout << "enum1Var2: " << enum1Var2 << endl; // 2
	cout << "enum1Var3: " << enum1Var3 << endl; // 2

	// enum class example: no redeclaration issues as with pure enum
	enum class enum3_t { enum_a, enum_b, enum_c };
	enum class enum4_t { enum_a, enum_b, enum_c };

	enum3_t enum3Var = enum3_t::enum_a;
	enum enum4_t enum4Var = enum4_t::enum_a;

	cout << (int) enum3Var << endl; // 0
	cout << (int) enum4Var << endl; // 0

	// struct example
	struct a_struct_t
	{
		int public_var;
	private:
		int private_var;
	public:
		a_struct_t() : public_var {2}, private_var {5} {} // initializer list
		~a_struct_t() { cout << "cleanup\n"; }
		void cout_private_var() { cout << private_var << endl; }
	};

	struct a_struct_t s;
	s.cout_private_var(); // 5
	cout << s.public_var << endl; // 2

	cout << sizeof(s) << endl; // 8
	memset(&s, 0, sizeof(s));
	s.cout_private_var(); // 0
}
