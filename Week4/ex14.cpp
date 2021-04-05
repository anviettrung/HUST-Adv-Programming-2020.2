#include <iostream>
#include <iterator>
#include <fstream>
#include <map>

using namespace std;

int main()
{
	map<int, int> counter;
	int n = 0;
	int* a;
	ifstream ifile("number.txt");

	ifile >> n;
	a = new int[n];
	for (int i = 0; i < n; i++) {
		ifile >> a[i];
		cout << a[i] << " ";
	}
	cout << endl;
	ifile.close();

	for (int i = 0; i < n; i++) {
		counter[a[i]]++;
	}

	int max = 0;
	for(map<int,int>::iterator it = counter.begin(); it != counter.end(); ++it) {
		if (it->second > max)
			max = it->second;
	}

	cout << "Highest frequency: " << max << endl;
	cout << "Numbers with highest frequency: ";

	for(map<int,int>::iterator it = counter.begin(); it != counter.end(); ++it) {
		if (it->second == max)
			cout << it->first << " ";
	}
	cout << endl;

	return 0;
}