#include <iostream>
#include <fstream>

using namespace std;

void Swap(char* a, char* b) 
{
	char t = *a;
	*a = *b;
	*b = t;
}

void Permutation(char* s, int l, int r, ofstream& out)
{
	if (l == r)
		out << s << endl;

	for (int i = l; i <= r; i++) {
		Swap(&s[l], &s[i]);

		Permutation(s, l+1, r, out);

		Swap(&s[l], &s[i]);
	}
}


int main() {
	int n = 0;
	char* s;
	cout << "N = ";
	cin >> n;

	s = new char[n];
	for (int i = 0; i < n; i++)
		s[i] = '1' + i;

	ofstream out("permutation.txt");
	Permutation(s, 0, n-1, out);
	out.close();

	return 0;
}