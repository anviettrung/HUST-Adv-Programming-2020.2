#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ================================
// Utility
// ================================
void Swap(int* a, int* b);
bool AscendingOrder(int e1, int e2);
bool DescendingOrder(int e1, int e2);

// ================================
// Sorting algorithm
// ================================
// Return rule
// if (index(e1) < index(e2)) then
//     "true"  if (e1, e2 is at right order)
//     "false" if (e1, e2 is at wrong order)
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
void QuickSort(int* a, int n, SortOrder ordered);
void QuickSortFullCall(int* a, int low, int high, SortOrder ordered);
int  Partition(int* a, int low, int high, SortOrder ordered);
// --------------------------------
void ShellSort(int* a, int n, SortOrder ordered);
// void CountingSort(int* a, int n, SortOrder ordered);

SortFunction f_sorts[] = {
	InsertionSort, // 0
	SelectionSort, // 1
	BubbleSort,    // 2
	MergeSort,     // 3
	HeapSort,      // 4
	QuickSort,     // 5
	ShellSort      // 6
};


// ================================
// MAIN PROGRAM
// ================================
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
// Utility Implement
// ================================
void Swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

bool AscendingOrder(int e1, int e2)
{
	return e1 <= e2;
}

bool DescendingOrder(int e1, int e2)
{
	return e1 >= e2;
}

// ================================
// Sorting algorithm Implement
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
void QuickSort(int* a, int n, SortOrder ordered)
{
	QuickSortFullCall(a, 0, n-1, ordered);
}
void QuickSortFullCall(int* a, int low, int high, SortOrder ordered)
{
	if (low < high) {
		int p_index = Partition(a, low, high, ordered);

		QuickSortFullCall(a, low, p_index-1, ordered);
		QuickSortFullCall(a, p_index+1, high, ordered);
	}
}
int Partition(int* a, int low, int high, SortOrder ordered)
{
	int pivot = a[high];
	int i = (low-1);

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (ordered(a[j], pivot)) {
			i++; // increment index of smaller element
			Swap(&a[i], &a[j]);
		}
    }
	Swap(&a[i + 1], &a[high]);

    return (i + 1);
}
// --------------------------------
void ShellSort(int* a, int n, SortOrder ordered)
{
	for (int gap = n/2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int t = a[i];
			int j;

			for (j = i; j >= gap && !ordered(a[j - gap], t); j -= gap)
				a[j] = a[j - gap];

			a[j] = t;
		}
	}
}
// --------------------------------
// void CountingSort(int* a, int n, SortOrder ordered);