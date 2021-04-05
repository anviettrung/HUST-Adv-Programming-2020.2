#include <iostream>

using namespace std;

int GCD(int x, int y)
{
	if (x == y) return x;
	if (x == 0) return y;
	if (y == 0) return x;

	if (x > y)
		return GCD(x % y, y);
	else
		return GCD(x, y % x);
}

int main()
{
	int a, b;

	cout << "a = ";
	cin >> a;

	cout << "b = ";
	cin >> b;

	cout << "GCD(a, b) = " << GCD(a, b) << endl;

	return 0;
}