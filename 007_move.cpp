//
// File name: 007_move.cpp
// Date: 2017-11-13
//
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

//#define DEBUG_MODE
#ifdef DEBUG_MODE
#define DBGOUT(args) cout << "[DBGOUT:] " << args
#else
#define DBGOUT(args)
#endif

class custom
{
private:
	int *x;
public:
	static const int INVVAL = -1;

	custom() : x(new int(0))
	{
		DBGOUT("standard constructor\n");
	}

	custom(int x) : x(new int(x))
	{
		DBGOUT("constructor\n");
	}

	~custom()
	{
		DBGOUT("destructor\n");

		if (x != nullptr)
		{
			delete x;
			x = nullptr;
		}
	}

	custom(const custom& t)
	{
		DBGOUT("copy constructor\n");

		x = t.x != nullptr ? new int(*t.x) : nullptr;
	}

	custom& operator=(const custom& t)
	{
		DBGOUT("copy assignment\n");

		if (&t == this) // self-check
			return *this;

		if (x != nullptr)
		{
			delete x; // free the object's data
			x = nullptr;
		}

		if (t.x != nullptr)
			x = new int(*t.x); // copy data

		return *this;
	}

	custom& operator=(custom&& t)
	{
		DBGOUT("move assignment\n");

		if (&t == this) // self-check
			return *this;

		if (x != nullptr)
		{
			delete x; // free the object's data
			x = nullptr;
		}

		x = t.x; // move instructions
		t.x = nullptr;

		return *this;
	}

	custom(custom&& t)
	{
		DBGOUT("move constructor\n");

		x = nullptr; // make sure no random value

		*this = move(t); // reuse the move assignment code
	}

	int val() const
	{
		return x != nullptr ? *x : INVVAL;
	}

	void val(int x)
	{
		if (this->x != nullptr)
			*this->x = x;
	}
};

bool operator==(const custom& a, const custom& b)
{
	if (a.val() == custom::INVVAL || b.val() == custom::INVVAL)
		return false;

	return a.val() == b.val();
}

custom move_stack_object()
{
	custom object(42);
	/* Note: the destructor for object is still called. */
	return move(object);
}

custom pseudo_copy_object()
{
	custom object(42);
	/* Compiler optimization: no copy instructions (and no destructor call) are involved on return. */
	return object;
}

void prevent_leaks()
{
	vector<custom*> v1;

	v1.push_back(new custom());

	// v1: we have to delete all data elements before leaving the function
	for (custom *x : v1)
		delete x;

	vector<unique_ptr<custom>> v2;

	v2.push_back(unique_ptr<custom>(new custom()));

	// v2: the unique_ptr will call delete for us so we can't forget it
}

int main()
{
	custom a, b;

	a.val(1);
	cout << a.val() << ", " << b.val() << endl; // 1, 0

	/* Test: copy assignment. */
	b = a;
	cout << a.val() << ", " << b.val() << endl; // 1, 1

	/* Test: move assignment. */
	b = move(a);
	cout << a.val() << ", " << b.val() << endl; // -1, 1

	/* Test: copy constructor. */
	custom c = b;
	cout << c.val() << endl; // 1

	/* Test: move constructor. */
	custom d = move(b);
	cout << d.val() << endl; // 1

	/* Test: copy an already moved object. */
	c = b;
	cout << c.val() << endl; // -1

	/* Test: move an already moved object. */
	c = move(b);
	cout << c.val() << endl; // -1

	custom x = move_stack_object();
	cout << x.val() << endl; // 42

	custom y = pseudo_copy_object();
	cout << y.val() << endl; // 42

	prevent_leaks();

	custom z1 = 42;
	custom z2(42);

	bool equal = z1 == z2;
	cout << boolalpha << equal << endl; // true
}
