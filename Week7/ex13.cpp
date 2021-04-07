#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int a[200];
int res[200];

int Find(int M, int r, int k = 0) 
{
	if (M == 0)
		return k;
	if (r < 0)
		return -1;

	while (a[r] > M)
		r--;

	int tempK = Find(M - a[r], r-1, k+1);
	if (tempK > 0) {
		res[k] = a[r];
		return tempK;
	}

	tempK = Find(M, r-1, k);
	if (tempK > 0)
		return tempK;

	return -1;
}

void sort(int n);

int main()
{
	ifstream input("thueGTGT.txt");

	int n, m;

	input >> n >> m;
	for (int i = 0; i < n; i++)
		input >> a[i];

	input.close();

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	sort(n);
	int resLeng = Find(m, n-1, 0);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	milliseconds ms_int = duration_cast<milliseconds>(t2 - t1);

	if (resLeng > 0) {
		cout << "Set Length = " << resLeng << endl << "[";
		for (int i = 0; i < resLeng-1; i++)
			cout << res[i] << ",";
		cout << res[resLeng-1] << "]" << endl;
	} else {
		cout << "Not found!" << endl;
	}

	cout << endl << "Runtime: " << ms_int.count() << "ms" << endl;

	ofstream output("result.txt");

	output << "M = " << m << endl;
	output << "Result Set Length = " << resLeng << endl;
	for (int i = 0; i < resLeng; i++) {
		output << res[i] << endl;
	}

	output.close();

	return 0;
}

void sort(int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++)
			if (a[i] > a[j]) {
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
	}
}