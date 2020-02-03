//
// File name: 006_classes.cpp
// Date: 2017-10-29
//
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

namespace geo
{
	// abstract class ("base class", "super class") has no constructor and has virtual destructor
	class primitive
	{
	public:
		virtual double area() const = 0; // subclass *MUST* implement this method
		virtual string myname() const { return "Primitive"; } // subclass *MAY* override this method
		virtual ~primitive() { }
	};

	// sub class (rectangle is inherited from primitive)
	class rectangle : public primitive
	{
	private: // no access from outside this class
		double *a;
	protected: // subclass can access these members
		double l, w;
		void update_a() { *a = l * w; }
	public: // interface to the public
		// standard constructor (to force initialization)
		rectangle(void) : l {0}, w {0} { a = new double; update_a(); }

		// other constructors
		rectangle(double l, double w) : l {l}, w {w} { a = new double; update_a(); }

		// constructor prototype
		rectangle(initializer_list<double> dimensions);

		// destructor
		~rectangle() { delete a; }

		// const functions
		double length() const { return l; }
		double width() const { return w; }
		double area() const { return *a; } // must override

		string myname() const override { return "Rectangle"; } // override this function is optional, also the "override" keyword is optional

		// manipulation functions
		inline void length(double l) { this->l = l; update_a(); }  // force inline (not needed because inline is default)
		void width(double w)  { this->w = w; update_a(); }

		// operator functions
		rectangle& operator+=(const rectangle& r) { l += r.l; w += r.w; update_a(); return *this; }
	};

	// function not accessing private data
	bool operator==(const rectangle& r1, const rectangle& r2)
	{
		return r1.length() == r2.length() && r1.width() == r2.width();
	}

	// implement constructor
	rectangle::rectangle(initializer_list<double> lst)
	{
		if (lst.size() != 2)
			throw length_error("expect list with length and width");

		double dim[2];

		copy(lst.begin(), lst.end(), dim);

		l = dim[0];
		w = dim[1];

		a = new double;

		update_a();
	}

	// class hierarchy: square -> rectangle -> primitive
	class square : public rectangle
	{
	public:
		// call constructors from rectangle class
		square() : rectangle() {}
		square(double s) : rectangle(s, s) {}

		string myname() const override { return "Square"; }

		// override these to guarantee that the width and the length are equal
		void length(double l) { this->l = l; this->w = l; update_a(); }
		void width(double w) { length(w); update_a(); }
	};

	// use abstract classes
	void print_name(const primitive& obj)
	{
		cout << obj.myname() << endl;
	}
}

int main()
{
	geo::rectangle recA;
	geo::rectangle recB(1., 1.);

	cout << "area recA = " << recA.area() << endl; // 0
	cout << "area recB = " << recB.area() << endl; // 1

	recA.length(1);
	recA.width(1);

	recB += recA;

	cout << "area recB = " << recB.area() << endl; // 4

	(recB += recA) += recA;

	cout << "area recB = " << recB.area() << endl; // 16

	recA.length(4.);
	recA.width(4.);

	if (recA == recB)
		cout << "rectangles are equal\n";

	if (operator==(recA, recB))
		cout << "rectangles are equal\n";

	geo::print_name(recA); // "Rectangle"

	geo::rectangle recC {3., 3.}; // initializer list
	cout << "area recC = " << recC.area() << endl; // 9

	geo::primitive *primitive = new geo::rectangle();
	delete primitive; // the virtual destructor allows us to use delete on a abstract type

	// Using objects of type square
	geo::square squareA(1), squareB(3);
	cout << squareA.myname() << endl;
	cout << squareA.area() << endl; // 1
	squareA.length(2);
	cout << squareA.area() << endl; // 4
	squareA.width(3);
	cout << squareA.area() << endl; // 9
	if (squareA == squareB)
		cout << "squares are equal\n";

	geo::primitive *p[] = {&recA, &recB, &recC, &squareA, &squareB };
	// retrieve type information
	for (geo::primitive *x : p)
		if (dynamic_cast<geo::square*>(x) != nullptr)
			cout << "square found\n";
		else if (dynamic_cast<geo::rectangle*>(x) != nullptr)
			cout << "rectangle found\n";
}
