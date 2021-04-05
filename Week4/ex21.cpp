#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int n, m, pos = -1;
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

	cout << "Reverse:" << endl;
	for (int* p = a+n-1; p >= a; p--)
		cout << *p << " ";
	cout << endl;

	return 0;
}