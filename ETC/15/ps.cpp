#include <stdio.h>
#include <time.h>
#include <stdlib.h> 

typedef struct ps {
	int tu;
	int mau;
} PS;

// ================================
// Utility
// ================================
void Swap(PS* a, PS* b);
bool AscendingOrder(PS e1, PS e2);

// ================================
// Sorting algorithm
// ================================
// Return rule
// if (index(e1) < index(e2)) then
//     "true"  if (e1, e2 is at right order)
//     "false" if (e1, e2 is at wrong order)
typedef bool (*SortOrder)(PS e1, PS e2); 
typedef void (*SortFunction)(PS* a, int n, SortOrder ordered);

void QuickSort(PS* a, int n, SortOrder ordered);
void QuickSortFullCall(PS* a, int low, int high, SortOrder ordered);
int  Partition(PS* a, int low, int high, SortOrder ordered);

int BinarySearch(PS* a, int l, int r, PS value, SortOrder ordered);

int main()
{
	int n = 10, res;
	PS tim;
	PS a[10];

	srand(time(NULL));   // Initialization, should only be called once.

	for (int i = 0; i < n; i++) {
		a[i].tu = rand() % 100;
		a[i].mau = rand() % 100;
	}

	printf("Mang ban dau:\n");
	for (int i = 0; i < n; i++) {
		printf("a[%d] = %d / %d\n", i, a[i].tu, a[i].mau);
	}

	QuickSort(a, n, AscendingOrder);

	printf("Mang sap xep:\n");
	for (int i = 0; i < n; i++) {
		printf("a[%d] = %d / %d\n", i, a[i].tu, a[i].mau);
	}

	printf("Nhap gia tri can tim\n");
	printf("Tu: ");
	scanf("%d", &tim.tu);
	printf("Mau: ");
	scanf("%d", &tim.mau);

	res = BinarySearch(a, 0, n-1, tim, AscendingOrder);
	if (res < 0)
		printf("Khong tim thay phan tu\n");
	else
		printf("Phan tu o vi tri: %d\n", res);
}

void Swap(PS* a, PS* b)
{
	PS t = *a;
	*a = *b;
	*b = t;
}

bool AscendingOrder(PS e1, PS e2)
{
	return e1.tu * e2.mau <= e2.tu * e1.mau;
}

int BinarySearch(PS* a, int l, int r, PS value, SortOrder ordered) {
	int res = (l + r) / 2;

	if (a[res].tu == value.tu && a[res].mau == value.mau) {
		return res;
	} else if (l >= r) {
		return -1; // can't find
	} else if (ordered(a[res], value)) {
		return BinarySearch(a, res, r, value, ordered);
	} else {
		return BinarySearch(a, l, res, value, ordered);
	}
}

// --------------------------------
void QuickSort(PS* a, int n, SortOrder ordered)
{
	QuickSortFullCall(a, 0, n-1, ordered);
}
void QuickSortFullCall(PS* a, int low, int high, SortOrder ordered)
{
	if (low < high) {
		int p_index = Partition(a, low, high, ordered);

		QuickSortFullCall(a, low, p_index-1, ordered);
		QuickSortFullCall(a, p_index+1, high, ordered);
	}
}
int Partition(PS* a, int low, int high, SortOrder ordered)
{
	PS pivot = a[high];
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