#include <iostream>
#include <fstream>

using namespace std;

#define INPFILE_NAME "sample-array.txt"
#define OUTFILE_NAME "Average Distance.txt"

int n = 10;
int* a;

void ReadArray(ifstream& in)
{
	a = new int[n];

	for (int i = 0; i < n; i++)
		in >> a[i];
}

void PrintResult(ofstream& out, float ans)
{
	out << ans << endl;
}

float AverageDistance(int* a, int n) 
{
	float ans = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++)
			ans += (float)abs(a[i] - a[j]);
	}

	ans /= n * (n-1) / 2;

	return ans;
}

int main()
{
	cout << "N = ";
	cin >> n;

	ifstream in(INPFILE_NAME);
	ReadArray(in);
	in.close();

	ofstream out(OUTFILE_NAME);
	float ans = AverageDistance(a, n);
	cout << "Average Distance = " << ans << endl;
	PrintResult(out, ans);
	out.close();

	return 0;
}