#include <iostream>

using namespace std;

void PrintLine(char c, int n);

int main()
{
	int h = 0;

	cout << "Nhập chiều cao cây: ";
	cin >> h;

	for (int i = 1; i <= h; i++) {
		PrintLine(' ', h - i);
		PrintLine('*', 2 * i - 1);
		cout << endl;
	}

	for (int i = 0; i < 3; i++) {
		PrintLine(' ', h - 2);
		cout << "| |" << endl;
	}

	return 0;
}

void PrintLine(char c, int n) 
{
	for (int i = 0; i < n; i++)
		cout << c;
}