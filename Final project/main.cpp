#include <stdio.h>
#include <iostream>
#include "system.h"
#include "adv_print.h"
#include "Polynomial.h"

using namespace avt_sys;
using namespace adv_print;
using namespace std;

// ============================
// DEFINITION
// ============================
#define PROJECT_SETTINGS_FILE "project-settings.txt"

// ============================
// CONSTANT
// ============================
#define MAX_FILE_NAME_SIZE 256
static double default_epsilon = 0.001f;
static int precision = 4;

// ============================
// GLOBAL VARIABLE
// ============================
FILE * ps_file;
FILE * inp;

Polynomial poly;
char ans = '0';

// ============================
// MAIN FUNCTION
// ============================
int Initialization();
void Destruction();

void MainMenu_Layout();
void Function_Layout(char id);

int Read_Interval_Layout(Interval* res);
double Read_Epsilon_Layout();

// ============================
// MAIN PROGRAM
// ============================
int main()
{
	// Nếu khởi tạo không thành công thì thoát chương trình
	int err = Initialization();
	if ( err > 0 ) {
		printf("Khởi tạo thất bại. error code: %d\n", err);
		Destruction();
		return 0;
	}

	ScrollScreen();

	while (ans != 'x') {
		if ('0' <= ans && ans <= '5')
			ClearScreen();
		switch (ans) {
			case '0':
				MainMenu_Layout();
				break;
			default:
				Function_Layout(ans);
				break;
		}

		ans = GetInput();
	}

	print_command("Kết thúc chương trình");

	ClearScreen();
	Destruction();
	return 0;
}

// ============================
// IMPLEMENT
// ============================
int Initialization() 
{
	char buff[MAX_FILE_NAME_SIZE];
	int n, e;
	double c;

	// Đọc file project settings
	ps_file = fopen(PROJECT_SETTINGS_FILE, "r");
	if (ps_file == NULL) 
		return 1;

	// Đọc file input
	fgets(buff, MAX_FILE_NAME_SIZE, ps_file);
	buff[strcspn(buff, "\n")] = 0; // remove '\n' character
	inp = fopen(buff, "r");
	if (inp == NULL)
		return 2;

	// Khởi tạo đa thức
	fscanf(inp, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(inp, "%d %lf", &e, &c);
		poly.Insert_Node(e, c);
	}

	// Mở file output
	fgets(buff, MAX_FILE_NAME_SIZE, ps_file);
	init_output_file(buff, "w");
	if (adv_print::fout == NULL)
		return 3;

	// Khởi tạo hằng số
	fscanf(ps_file, "%d", &precision);
	p_precision = precision;
	fscanf(ps_file, "%lf", &default_epsilon);

	print_command("Khởi tạo chương trình thành công");
	return 0;
}

void Destruction()
{
	fclose(ps_file);
	fclose(inp);
	close_output_file();
}

void MainMenu_Layout() 
{
	cout << "=== Menu Chính ===" << endl
		 << "Đa thức: "; poly.Print();
	cout << endl;
	cout << "[1] Tìm miền chứa nghiệm" << endl
		 << "[2] Tìm các khoảng phân ly (a,b) thoả mãn |b-a| <= 0.5" << endl
		 << "[3] Tìm nghiệm gần đúng với số lần lặp n" << endl
		 << "[4] Tìm nghiệm gần đúng với sai số e" << endl
		 << "[5] Tìm nghiệm gần đúng x_n thoả mãn |xn - xn-1| <= e " << endl
		 << "[x] Thoát";
}

void Function_Layout(char id)
{
	Interval interval;
	double e, x0;
	int n;

	switch (id) {
		case '1':
			print_command("Tìm miền chứa nghiệm");

			interval = poly.Get_Root_Interval();
			print("\tMiền chứa nghiệm là (%.*lf, %.*lf)\n", 
				precision, interval.left, 
				precision, interval.right);

			break;
		case '2':
			print_command("Tìm các khoảng phân ly");
			poly.Find_KPL(0.5f);
			break;
		case '3':
			print_command("Tìm nghiệm gần đúng với số lần lặp n");
			printf("Nhập số lần lặp n = ");
			scanf("%d", &n);
			print("\tSố lần lặp n là %d\n", n);

			switch (Read_Interval_Layout(&interval)) {
				case 1:
				x0 = Newton_Raphson(&poly, interval.left, interval.right, n, true);
				print("\n\tNghiệm x là %.*lf\n", precision, x0);
				break;
				case 2:
				break;
			}

			break;
		case '4':
			print_command("Tìm nghiệm gần đúng với sai số e");
			e = Read_Epsilon_Layout();

			switch (Read_Interval_Layout(&interval)) {
				case 1:
				x0 = Newton_Raphson_Err_Formula(&poly, interval.left, interval.right, e, true);
				print("\n\tNghiệm x là %.*lf\n", precision, x0);
				break;
				case 2:
				break;
			}
			break;
		case '5':
			print_command("Tìm nghiệm gần đúng x_n");
			e = Read_Epsilon_Layout();

			switch (Read_Interval_Layout(&interval)) {
				case 1:
					x0 = Newton_Raphson(&poly, interval.left, interval.right, e, true);
					print("\n\tNghiệm x_n là %.*lf\n", precision, x0);
					break;
				case 2:
				break;
			}
			break;

		default:
			return;
	}

	cout << endl << endl
		 << "[0] Về menu chính" << endl
		 << "[x] Thoát";
}

int Read_Interval_Layout(Interval* res)
{
	bool valid;

	printf("\"Nhập (a, b) = (0, 0) nếu muốn sử dụng các khoảng phân ly mặc định!\"\n");
	printf("Nhập khoảng phân ly (a, b) = ");
	*res = Read_Interval();

	valid = res->left != 0 || res->right != 0;
	if (valid) {
		print("\tKhoảng phân ly đã nhập là (%.*lf, %.*lf)\n", precision, res->left, precision, res->right);
		if (poly.Is_KPL(*res) == false) {
			print("\tKhoảng đã nhập không phải khoảng phân ly!\n");
			return 0;
		}
		return 1;
	}
	else {
		print("\tSử dụng các khoảng phân ly mặc định\n");
		return 2;
	}
}

double Read_Epsilon_Layout()
{
	double e;

	printf("\"Nhập e = 0 nếu muốn sử dụng hằng số epsilon mặc định!\"\n");
	printf("Nhập sai số e = ");
	scanf("%lf", &e);
	e = e != 0 ? e : default_epsilon;

	print("\tSai số epsilon đã nhập là %.*lf\n", precision, e);

	return e;
}

