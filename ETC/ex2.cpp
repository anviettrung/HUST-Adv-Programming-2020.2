#include <iostream>

using namespace std;

int main()
{
	int count[10];
	for (int i = 0; i < 10; i++) {
		count[i] = 0;
	}

	cout << "Nhap so (dung chuong trinh thi nhap 'x'" << endl;

	char t = '0';
	int ans = 0;
	while (t != 'x') {
		t = getchar();
		ans = t - '0';
		if (ans >= 0 && ans < 10)
			count[ans]++;
	}

	cout << endl;

	for (int i = 0; i < 10; i++) {
		cout << "So " << i << " nhap: " << count[i] << " lan." << endl;
	}

	return 0;
}