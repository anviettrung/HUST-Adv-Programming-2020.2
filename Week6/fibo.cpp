#include <iostream>

using namespace std;

long long fibonaci(int n) {
	long long a[2];
	int c = 3;

	a[0] = a[1] = 1;

	if (n <= 0)
		return -1;

	while (c <= n) {
		a[c % 2] = a[0] + a[1];
		c++;
	}

	return a[n % 2];
}

int main()
{
	int n = 0;
	cout << "N = ";
	cin >> n;

	if (n > 0)
		cout << "Fibonaci " << n << "th: " << fibonaci(n) << endl;
	else
		cout << "N must be positive number!" << endl;

	return 0;
}