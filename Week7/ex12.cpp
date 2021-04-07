#include <iostream>
#include <fstream>

using namespace std;

#define INPFILE_NAME "sample-array.txt"
#define OUTFILE_NAME "duplicate.txt"

int n = 10;
int* a;

void ReadArray(istream& in)
{
	a = new int[n];

	for (int i = 0; i < n; i++)
		in >> a[i];
}

void PrintResult(ofstream& out, int* ans, int m)
{
	for (int i = 0; i < m; i++)
		out << ans[i] << " ";
}

void Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int RemoveDuplicate(int* a, int n) 
{
	int m = n;

	for (int i = 1; i < m; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i] == a[j]) {
				m--;
				Swap(&a[i], &a[m]);
				i--;
				break;
			}
		}
	}

	return m;
}

int main()
{
	cout << "N = ";
	cin >> n;

	ifstream in(INPFILE_NAME);
	ReadArray(in);
	in.close();

	ofstream out(OUTFILE_NAME);
	PrintResult(out, a, RemoveDuplicate(a, n));
	out.close();

	return 0;
}