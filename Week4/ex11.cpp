#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
	int m, min, max;
	bool existM = false;

	int n = 0;
	int* a;
	ifstream ifile("number.txt");

	ifile >> n;
	a = new int[n];
	for (int i = 0; i < n; i++) {
		ifile >> a[i];
		cout << a[i] << " ";
	}
	cout << endl;
	ifile.close();

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