#include <iostream>

using namespace std;

int bisearch(int arr[], int val, int l, int r);

int main(int argc, char const *argv[])
{
	int n, m, pos = -1;
	int a[1000];

	cout << "n = ";
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	// Sort
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if (a[i] > a[j]) {
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
			}

	cout << "Sorted Array: " << endl;
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;

	cout << "Finding value: ";
	cin >> m;

	pos = bisearch(a, m, 0, n-1);
	if (pos > 0)
		cout << "Element value " << m << " exists at index " << pos << endl;
	else 
		cout << "Element value " << m << " doesn't exists!" << endl;

	return 0;
}

int bisearch(int arr[], int val, int l, int r)
{
	int mid = (l + r) / 2;
	if (arr[mid] == val) return mid;
	if (l == r) return -1;

	return arr[mid] > val ? bisearch(arr, val, l, mid-1) : bisearch(arr, val, mid+1, r);
}










