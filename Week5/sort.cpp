#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ================================
// Utility
// ================================
void Swap(int* a, int* b);
bool AscendingOrder(int e_left, int e_right);

// ================================
// Sorting algorithm
// ================================
typedef bool (*SortOrder)(int e1, int e2);
typedef void (*SortFunction)(int* a, int n, SortOrder ordered);

// --------------------------------
void InsertionSort(int* a, int n, SortOrder ordered);
void SelectionSort(int* a, int n, SortOrder ordered);
void BubbleSort(int* a, int n, SortOrder ordered);
// // --------------------------------
void MergeSort(int* a, int n, SortOrder ordered);
void MergeSortFullCall(int* a, int left, int right, SortOrder ordered);
void Merge(int* a, int left, int mid, int right, SortOrder ordered);
// // --------------------------------
void HeapSort(int* a, int n, SortOrder ordered);
void Heapify(int* a, int n, int nodeID, SortOrder ordered);
// --------------------------------
// int QuickSort(int* a, int n, SortOrder ordered);
// int ShellSort(int* a, int n, SortOrder ordered);
// int CountingSort(int* a, int n, SortOrder ordered);

SortFunction f_sorts[] = {
	InsertionSort,
	SelectionSort,
	BubbleSort,
	MergeSort,
	HeapSort
};

int main()
{
	int n = 3, fsortIndex = 0;
	int* arr;
	ifstream fin("random_int_array.txt");
	ofstream fout("result.txt");

	// INPUT
	cout << "N (max 10^6) = ";
	cin >> n;
	cout << "Sort Function Number = ";
	cin >> fsortIndex;

	arr = new int[n];
	for (int i = 0; i < n; i++)
		fin >> arr[i];

	fin.close();

	// PROCESS
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	f_sorts[fsortIndex](arr, n, AscendingOrder);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	milliseconds ms_int = duration_cast<milliseconds>(t2 - t1);
	int sort_time = ms_int.count();

	// OUTPUT
	cout << "Runtime: " << sort_time << "ms" << endl;

	for (int i = 0; i < n; i++)
		fout << arr[i] << endl;

	fout.close();
	return 0;
}

// ================================
// Utility
// ================================
void Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

bool AscendingOrder(int e_left, int e_right)
{
	return e_left <= e_right;
}

// ================================
// Sorting algorithm
// ================================
void InsertionSort(int* a, int n, SortOrder ordered)
{
	int key, j;
	for (int i = 1; i < n; i++) {

		key = a[i];
		j = i - 1;

		while (j >= 0 && !ordered(a[j], key)) {
			a[j + 1] = a[j];
			j -= 1;
		}

		a[j + 1] = key;
	}
}

void SelectionSort(int* a, int n, SortOrder ordered)
{
	int min;
	int e;
	for (int i = 0; i < n; i++) {
		min = a[i];
		e = i;
		for (int j = i+1; j < n; j++)
			if (!ordered(min, a[j])) {
				min = a[j];
				e = j;
			}
		Swap(&a[i], &a[e]);
	}
}

void BubbleSort(int* a, int n, SortOrder ordered)
{
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if (!ordered(a[i], a[j]))
				Swap(&a[i], &a[j]);
}

// --------------------------------
void MergeSort(int* a, int n, SortOrder ordered)
{
	MergeSortFullCall(a, 0, n-1, ordered);
}

void MergeSortFullCall(int* a, int left, int right, SortOrder ordered)
{
	if (left < right) {
		int mid = left + (right - left) / 2;
		MergeSortFullCall(a, left, mid, ordered);
		MergeSortFullCall(a, mid+1, right, ordered);

		Merge(a, left, mid, right, ordered);
	}
}

void Merge(int* a, int left, int mid, int right, SortOrder ordered)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Copy 2 parts of array
	int Larr[n1], Rarr[n2];

	for (int i = 0; i < n1; i++)
		Larr[i] = a[left + i];

	for (int i = 0; i < n2; i++)
		Rarr[i] = a[mid + i + 1];

	int track1 = 0;
	int track2 = 0;
	int k = left;

	while (track1 < n1 && track2 < n2) {
		if (ordered(Larr[track1], Rarr[track2])) {
			a[k] = Larr[track1];
			track1++;
		} else {
			a[k] = Rarr[track2];
			track2++;
		}
		k++;
	}

	while (track1 < n1) {
		a[k] = Larr[track1];
		track1++;
		k++;
	}

	while (track2 < n2) {
		a[k] = Rarr[track2];
		track2++;
		k++;
	}
}
// --------------------------------
void HeapSort(int* a, int n, SortOrder ordered)
{
	// Build heap
	for (int i = n/2 - 1; i >= 0; i--)
		Heapify(a, n, i, ordered);

	// Extract elements form heap
	for (int i = n-1; i > 0; i--) {
		Swap(&a[0], &a[i]);

		// reduce heap
		Heapify(a, i, 0, ordered);
	}
}

void Heapify(int* a, int n, int nodeID, SortOrder ordered)
{
	int largest = nodeID;
	int left = 2 * nodeID + 1;
	int right = 2 * nodeID + 2;

	// Left child larger than root
	if (left < n)
		if (!ordered(a[left], a[largest]))
			largest = left;

	// Right child larger than root
	if (right < n)
		if (!ordered(a[right], a[largest]))
			largest = right;

	if (largest != nodeID) {
		Swap(&a[nodeID], &a[largest]);

		Heapify(a, n, largest, ordered);
	}
}
// --------------------------------

// int QuickSort(int** a, int n, SortOrder ordered);
// int ShellSort(int** a, int n, SortOrder ordered);
// int CountingSort(int** a, int n, SortOrder ordered);