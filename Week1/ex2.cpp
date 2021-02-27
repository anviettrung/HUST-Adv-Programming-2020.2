#include <iostream>

using namespace std;

int main()
{
	char name[50];

	cout << "Nhập tên: ";
	cin.getline(name, sizeof(name));

	cout << "Chào bạn, mình đến với thế giới lập trình!" << endl
		 << "Mình tên là " << name << endl;

	return 0;
}