#include <iostream>
#include "menu.h"

using namespace std;

void A()
{
	cout << "A" << endl;
}

void B()
{
	cout << "B" << endl;
}

int main()
{
	Layout layouts[] = { A, B, A };

	Menu menu(3, layouts);
	menu.Print();

	return 0;
}