#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	int n, m, min, max;
	bool existM = false;
	int a[1000];

	cout << "n = ";
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	cout << "Finding value: ";
	cin >> m;

	min = a[0];
	max = a[0];

	for (int i = 0; i < n; i++) {
		min = a[i] < min ? a[i] : min;
		max = a[i] > max ? a[i] : max;
		existM = (existM) || (m == a[i]);
	}

	if (existM)
		cout << "Array has value " << m << endl;
	else
		cout << "Array doesn't have value " << m << endl;

	cout << "Min value = " << min << endl
		<< "Max value = " << max << endl;

	return 0;
}