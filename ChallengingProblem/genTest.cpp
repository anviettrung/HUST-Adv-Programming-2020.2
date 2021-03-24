#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int main()
{
	srand(time(NULL));

	ofstream test("input.txt");

	int n, m;

	cin >> n >> m;
	test << n << " " <<  m << endl;
	for (int i = 0; i < n; i++)
		test << rand() % (m / 100) + 1 << endl;

	test.close();

	return 0;
}