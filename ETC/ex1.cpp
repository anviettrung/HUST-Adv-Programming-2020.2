#include <iostream>

using namespace std;

int main()
{
	int n;

	bool first = true;
	do {
		if (!first)
			cout << "Nhap sai! Nhap lai so chan lon hon 0: " << endl;

		cout << "Nhap n: ";
		cin >> n;
		first = false;
	} while ((n <= 0) || (n % 2 == 1));

	int s = 0;
	int t = 1;
	for (int i = 2; i <= n; i += 2) {
		s += t * i * i;
		t *= -1;
	}

	cout << "S = " << s << endl;

	return 0;
}