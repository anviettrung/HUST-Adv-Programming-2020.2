#include <iostream>

using namespace std;

// ================================
// Field definition
// ================================
template <typename T>
class Complex {
public:
	T re;
	T im;

	Complex(T r = 0, T i = 0) {
		re = r;
		im = i;
	}

	Complex operator+(Complex const& obj) {
		return Complex(re + obj.re, im + obj.im);
	}

	Complex operator-(Complex const& obj) {
		return Complex(re - obj.re, im - obj.im);
	}

	Complex operator*(Complex const& obj) {
		return Complex(re * obj.re - im * obj.im, im * obj.re + re * obj.im);
	}

	Complex operator~() {
		return Complex(re, -im);
	}

	bool operator==(const Complex& obj) {
		return (re == obj.re) && (im == obj.im);
	}

	bool operator!=(const Complex& obj) {
		return (re != obj.re) || (im != obj.im);
	}

	void Print() {
		cout << re;
		if (im < 0)
			cout << im << "i";
		else
			cout << "+" << im << "i";

	}
};

int main()
{
	Complex<int> a(5, 5), b(5, 5);
	Complex<int> c = a *b;

	c.Print();
	cout << endl;

	return 0;
}
