#include <iostream>
#include <fstream>

using namespace std;

#define INPFILE_NAME "sample-array-2.txt"
#define OUTFILE_NAME "biggest-array.txt"

int n = 10;
int* a;
int* res;

void ReadArray(istream& in)
{
	a = new int[n];

	for (int i = 0; i < n; i++)
		in >> a[i];
}

void PrintResult(ofstream& out, int* ans, int m)
{
	out << m << endl;
	for (int i = 0; i < m; i++)
		out << ans[i] << " ";
}

void Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int FindLongest(int* a, int n) 
{
	int res_start = 0;
	int res_len = 0;
	int max = 0;

	int i = 0;
	while (i < n) {
		int sum = 0;
		int len = 0;
		int start = i;

		while (a[i] > 0) {
			sum += a[i];
			i++;
			len++;

			if (i == n)
				break;
		}

		if (sum > max) {
			max = sum;
			res_start = start;
			res_len = len;
		}

		if (i < n)
		while (a[i] <= 0) {
			i++;
			if (i == n)
				break;
		}
	}

	res = new int[res_len];
	for (int i = 0; i < res_len; i++)
		res[i] = a[res_start + i];

	return res_len;
}

int main()
{
	cout << "N = ";
	cin >> n;

	ifstream in(INPFILE_NAME);
	ReadArray(in);
	in.close();

	ofstream out(OUTFILE_NAME);
	int ansLen = FindLongest(a, n);

	PrintResult(out, res, ansLen);
	out.close();

	return 0;
}