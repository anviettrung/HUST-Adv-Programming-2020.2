#include <iostream>

using namespace std;

long S(int n)
{
	long s = 1;
	for (int i = 2; i <= 2*n; i++) {
		s *= i;
	}

	return s;
}

int main()
{
	int n;

	cout << "n = ";
	cin >> n;

	cout << "S(n) = (2n)! = " << S(n) << endl;

	return 0;
}