#include <iostream>
#include <math.h>

using namespace std;

#define _PI 3.14159
#define _E  2.71828
#define _EPSILON 0.0000000001

typedef double (*MathFunc)(double x);

double SimpleFunction(double x)
{
	return x*x*x + 2*x*x - 0.5 * _E * _PI;
}

double Solve(MathFunc f, double a, double b, double epsilon)
{
	double fafb = f(a) * f(b);

	if (fafb > 0) {
		return 0; // unexpected range
	} else if (fafb == 0) {
		return f(a) == 0 ? a : b;
	}

	// fafb < 0
	double c = (a + b) / 2;
	double E = fabs(b - a);

	while (E > epsilon) {
		if (f(a) * f(c) <= 0)
			b = c;
		else
			a = c;

		E = fabs(b - a);
		c = (a + b) / 2;
	}

	return a;
}

int main()
{
	double a, b;
	double res;
	MathFunc f = SimpleFunction;

	cout << "Range (a, b): " << endl;
	cin >> a >> b;

	res = Solve(f, a, b, _EPSILON);
	if (res == 0 && f(0) != 0)
		cout << "unexpected range (a, b)!" << endl;
	else
		cout << Solve(f, a, b, _EPSILON) << endl;

	return 0;
}