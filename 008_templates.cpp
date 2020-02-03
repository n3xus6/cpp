//
// File name: 008_templates.cpp
// Date: 2017-11-24
//
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

template<typename T, unsigned int MAX = numeric_limits<int>::max()>
class BasicArray
{
private:
	T* row;
	unsigned int len;
public:
	// Without explicit, the statement "BasicArray<char> = 3;"
	// would create an array with three char elements, for example.
	explicit BasicArray(unsigned int len);
	~BasicArray() { delete[] row; }
	unsigned int length() const { return len; }
	T& operator[](unsigned int i) const;
	using ValueType = T;
	// Access value argument (constexpr is optional).
	constexpr unsigned int max() const { return MAX; }
};

template<typename T, unsigned int max>
BasicArray<T, max>::BasicArray(unsigned int len)
{
	if (len == 0)
		throw length_error("Array of length zero not allowed.");

	if (len * sizeof(T) > this->max())
		throw length_error("The array would exceed it's maximum permitted size.");

	row = new T[len];
	this->len = len;
}

template<typename T, unsigned int max>
T& BasicArray<T, max>::operator[](unsigned int i) const
{
	if (i >= len)
		throw out_of_range("Array index invalid.");
	return row[i];
}


// begin() and end() needed for the range-based for statement
template<typename T>
T* begin(BasicArray<T>& arr) { return &arr[0]; }

template<typename T>
T* end(BasicArray<T>& arr)   { return &arr[0] + arr.length(); }


template<typename T>
void print(BasicArray<T>& arr)
{
	for (const T& x: arr)
		cout << x << ' ';
	cout << endl;
}

/* Example for a Variadic Template. */
void print_reverse() {} // stop the recursion if no argument left
template<typename FIRST, typename... NEXT>
void print_reverse(FIRST f, NEXT... n)
{
	print_reverse(n...);
	cout << f;
}

// functor implements operator() for a class
template<typename T>
class Mul
{
private:
	const T& factor;
public:
	explicit Mul(const T& factor) : factor(factor) {}
	~Mul() {}
	void operator()(T& v) const { v *= factor; }
};

// apply functor on container elements
template<typename C, typename OP>
void apply(C& c, OP op)
{
	for (auto& x : c)
		op(x);
}

using FloatPointArray = BasicArray<double>;

int main()
{
	BasicArray<char> char_array(3);

	char_array[0] = 'H';
	char_array[1] = 'i';
	char_array[2] = '!';

	print(char_array);

	BasicArray<int> int_array(2);

	int_array[0] = 4;
	int_array[1] = 2;

	print(int_array);

	FloatPointArray::ValueType pi = 3.14159265359; // access value type

	cout << pi << endl;

	try
	{
		// trying to fit 1000 Integers into 128 bytes will not work...
		BasicArray<int, 128> large_array(1000);
	}
	catch (length_error& e)
	{
		cout << e.what() << endl;
	}

	int_array[0] = 1;
	int_array[1] = 1;

	// functor example usage
	apply(int_array, Mul<int>{2});
	print(int_array); // 22

	// Lambda expression which creates a functor
	apply(int_array, [](int& x){ x*=2; });
	print(int_array); // 44

	int factor = 2;
	apply(int_array, [&factor](int& x){ x*=factor; });
	print(int_array); // 88

	// prints "Hello, world!"
	print_reverse('\n', '!','d','l','r','o','w',' ',',','o','l','l','e','H');


	float    e   = 2.71828;
	float *  ep  = &e;
	float &  er  = e;
	float *& epr = ep;

	cout <<  e   << ", "
		 << *ep  << ", "
		 <<  er  << ", "
		 // A reference-to-pointer variable is dereferenced like a pointer.
		 << *epr << endl;

	float e2 = e*2;
	// We update the pointer 'ep' via the reference-to-pointer variable 'epr':
	epr = &e2;
	cout << *ep << endl; // ... 5.43656
}
