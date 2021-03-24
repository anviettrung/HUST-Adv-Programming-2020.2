#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int main()
{
	srand(time(NULL));

	ofstream test("random_int_array.txt");

	int n, m;

	cin >> n >> m;

	for (int i = 0; i < n; i++)
		test << rand() % m << endl;

	test.close();

	return 0;
}