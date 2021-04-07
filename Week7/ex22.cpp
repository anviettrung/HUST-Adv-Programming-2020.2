#include <iostream>
#include <fstream>

using namespace std;

struct DiemHP {
	int hocphanID;
	int diem;

	DiemHP* next;
};

struct SVNode {
	int mssv;
	string name;
	DiemHP* diems;

	SVNode* next;
};

SVNode* danhsachSV;

int main()
{


	return 0;
}