#include <iostream>
#include <iomanip>

using namespace std;

int main() 
{
	double a, b, c;
	double n1, n2;
	double r, i; // cho so phuc
	int ans = 0;

	// Settings
	cout << setprecision(2) << fixed;

	// Quy uoc: 0 = vo nghiem | 1 = vo so nghiem | 2 = n0 bthg | 3 = n0 phuc
	cout << "Nhập hệ số a,b,c: ";
	cin >> a >> b >> c;

	if (a == 0) {

		if (b == 0) {
			if (c == 0)
				ans = 1;
			else
				ans = 0;
		} else {
			ans = 2;
			n1 = -c / b;
			n2 = n1;
		}

	} else {

		double delta = b*b - 4*a*c;
		if (delta < 0) {
			ans = 3;
			r = -b / (2*a);
			i = sqrt(fabs(delta)) / (2*a);
		} else {
			ans = 2;
			delta = sqrt(delta);
			n1 = (-b + delta) / (2*a);
			n2 = (-b - delta) / (2*a);
		}	
	}

	switch (ans) {
		case 0:
			cout << "Phương trình vô nghiệm!" << endl;
			break;
		case 1:
			cout << "Phương trình vô số nghiệm!" << endl;
			break;
		case 2:
			if (n1 == n2)
				cout << "Nghiệm kép: " << n1 << endl;
			else 
				cout << "2 nghiệm: " << n1 << " " << n2 << endl;
			break;
		case 3:
			cout << "Nghiệm phức: " << endl
				 << r << "+" << i << "i" << endl
				 << r << "-" << i << "i" << endl;
			break;
	}

	return 0;
}