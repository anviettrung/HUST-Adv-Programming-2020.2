#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <stdio.h>
#include <math.h>
#include "adv_print.h"

using namespace adv_print;

static int p_precision = 4;

// ============================
// Cấu trúc dữ liệu
// ============================

// Kiểu miền
typedef struct Interval {
	double left;  // Giới hạn trái
	double right; // Giới hạn phải
} Interval;

// Hạng tử trong đa thức
typedef struct PNode {
	double coeff; // Hệ số
	int exponent; // Bậc

	PNode* next;  // Hạng tử tiếp theo
} PNode;

// Đa thức
class Polynomial {
private:
	PNode* head;            // Danh sách các hạng tự
	Interval root_interval; // Miền chứa nghiệm

	bool found_root_interval; // đánh dấu để không tìm lại miền nghiệm nhiều lần
public:
	Polynomial();
	~Polynomial();

	// Thêm một hạng tử dạng cx^e vào đa thức
	void Insert_Node(int e, double c);

	// In hàm số
	void Print();

	// Tính giá trị đa thức tại điểm x
	double F(double x);

	// Tính giá trị đạo hàm tại điểm x
	double dF(double x);

	// Tính giá trị đạo hàm cấp 2 tại điểm x
	double ddF(double x);

	// Đổi đa thức từ f(x) sang f(-x)
	void Reverse_Odd_Exponent_Sign();

	// Tìm cận trên của miền nghiệm
	double Find_Root_Interval_Upper_Edge();

	// Tìm miền nghiệm
	void Find_Root_Interval();
	Interval Get_Root_Interval();

	// Tìm khoảng phân ly
	void Find_KPL(double e);

	// Kiểm tra xem có phải khoảng phân ly
	bool Is_KPL(double a, double b);
	bool Is_KPL(Interval interval);

	// Các công thức sai số
	double Err_Target_Form(double x, double m);
	double Err_DA_Form(double x, double px, double m, double M);
};

// Lặp n
double Newton_Raphson(Polynomial* f, double a, double b, int n, bool print_state = false);

// Sai số
double Newton_Raphson(Polynomial* f, double a, double b, double e, bool print_state = false);

// Sai số theo công thức
double Newton_Raphson_Err_Formula(Polynomial* f, double a, double b, double e, bool print_state = false);

// Các Hàm phụ trợ
// ---------------
int sign(double x);
double min(double a, double b);
double max(double a, double b);

Interval Read_Interval();

// Phương pháp chia đôi
Interval Bisection(Polynomial* f, double a, double b, double dist);
void Bisection(Polynomial* f, Interval* interval, double dist);

// ============================
// Khai triển class Polynomial
// ============================

Polynomial::Polynomial() { 
	head = NULL;
	found_root_interval = false;
}

Polynomial::~Polynomial() {
	PNode* cur = head;

	while (cur != NULL) {
		head = head->next;
		delete cur;
		cur = head;
	}
}

void Polynomial::Insert_Node(int e, double c) {
	PNode* new_node = (PNode*)malloc(sizeof(PNode));
	PNode* prev = NULL;
	PNode* cur = head;

	if ( new_node == NULL ) return; // space isn't available

	// Setup value
	new_node->exponent = e;
	new_node->coeff = c;

	// Loop to find the correct location in the list (descent)
	while ( cur != NULL && cur->exponent >= e) {
		prev = cur; 
		cur = cur->next; 
	}

	// Insert new node into list
	if (prev == NULL) {
		new_node->next = head;
		head = new_node;
	} else {
		if (prev->exponent == e) {
			prev->coeff += new_node->coeff;
			delete new_node;
		} else {
			prev->next = new_node;
			new_node->next = cur;
		}
	}

	found_root_interval = false;
}

void Polynomial::Print() {
	PNode* cur = head;

	while (cur != NULL) {
		if (cur != head) // not first node
			printf("%+.lf", cur->coeff);
		else		
			printf("%.lf", cur->coeff);

		switch (cur->exponent) {
			case 0: break;

			case 1: 
				printf("x ");
			break;

			default:
				printf("x^%d ", cur->exponent);
			break;
		}

		cur = cur->next;
	}
}

double Polynomial::F(double x) {
	if (head == NULL) return 0;

	double res = head->coeff;
	int degree = head->exponent;
	PNode* cur = head->next;

	while (cur != NULL) {
		while (cur->exponent < degree-1) {
			res *= x;
			degree--;
		}
		res = cur->coeff + res * x;
		degree--;

		cur = cur->next;
	}

	return res;
}

double Polynomial::dF(double x) {
	if (head == NULL) return 0;

	double res = head->coeff * head->exponent;
	int degree = head->exponent-1;
	PNode* cur = head->next;

	while (cur != NULL) {
		while (cur->exponent < degree-1) {
			res *= x;
			degree--;
		}
		res = cur->coeff * cur->exponent + res * x;
		degree--;

		cur = cur->next;
	}

	return res;
}

double Polynomial::ddF(double x) {
	if (head == NULL) return 0;

	double res = head->coeff * head->exponent * (head->exponent - 1);
	int degree = head->exponent-2;
	PNode* cur = head->next;

	while (cur != NULL) {
		while (cur->exponent < degree-2) {
			res *= x;
			degree--;
		}
		if (cur->exponent > 1)
			res = cur->coeff * cur->exponent * (cur->exponent - 1) + res * x;
		else
			res = res * x;
		degree--;

		cur = cur->next;
	}

	return res;
}

void Polynomial::Reverse_Odd_Exponent_Sign() {
	PNode* cur = head;
	while (cur != NULL) {
		if (cur->exponent % 2 == 1)
			cur->coeff = -cur->coeff;
		cur = cur->next;
	}
}

double Polynomial::Find_Root_Interval_Upper_Edge() {
	if (head == NULL) return 0;

	// sign of a0
	double sign = head->coeff < 0 ? -1.0f : 1.0f;
	int m = -1;
	double max;
	PNode* cur = head->next;

	while (cur != NULL) {
		if (cur->coeff * sign < 0) {
			m = head->exponent - cur->exponent;
			max = cur->coeff;
			break;
		}
		cur = cur->next;
	}

	// opposite sign coeffect is available
	if (m >= 0) {
		cur = head->next;
		while (cur != NULL) {
			if (cur->coeff * sign < 0) {
				if (fabs(cur->coeff) > fabs(max))
					max = cur->coeff;
			}

			cur = cur->next;
		}
		
		return 1 + pow(-max / head->coeff, 1.0f / m);
	} else {
		return 0;
	}
}

void Polynomial::Find_Root_Interval() {
	root_interval.right = Find_Root_Interval_Upper_Edge();

	// Temporary change f(x) to f(-x)
	Reverse_Odd_Exponent_Sign();

	root_interval.left = -Find_Root_Interval_Upper_Edge();

	// Change back to f(x)
	Reverse_Odd_Exponent_Sign();

	found_root_interval = true;
}

Interval Polynomial::Get_Root_Interval() {
	if (found_root_interval == false)
		Find_Root_Interval();

	return root_interval;
}

void Polynomial::Find_KPL(double e) {
	Interval ri = Get_Root_Interval();
	double k = (ri.right - ri.left) / head->exponent;
	double A = ri.left;
	double B = ri.right;

	Interval sInter;
	int count = 0;

	while (A <= B) {
		if (F(A) * F(A + k) < 0) {
			print("\tKPL %d ban đầu là (%lf, %lf)\n", ++count, A, A + k);
			sInter.left = A;
			sInter.right = A + k;
			Bisection(this, &sInter, e);
			print("\tKPL %d sau khi thu hẹp bằng PP chia đôi là (%lf, %lf)\n\n", count, sInter.left, sInter.right);
		}
		A = A + k;
	}
}

bool Polynomial::Is_KPL(double a, double b) {
	return F(a) * F(b) < 0;
}

bool Polynomial::Is_KPL(Interval interval) {
	return Is_KPL(interval.left, interval.right);
}

double Polynomial::Err_Target_Form(double x, double m) {
	return fabs(F(x) / m);
}

double Polynomial::Err_DA_Form(double x, double px, double m, double M) {
	return M * (x - px) * (x - px) / (2 * m);
}

// ============================
// Khai triển Thuật toán tiếp tuyến
// ============================
double Newton_Raphson(Polynomial* f, double a, double b, int n, bool print_state) {
	double x, x0;
	double px = 0;
	int count = 0;
	double m = min( fabs(f->dF(a)), fabs(f->dF(b)) );
	double M = max( fabs(f->ddF(a)), fabs(f->ddF(b)) );
	double err;

	// Chọn điểm Fourier
	if (sign(f->F(a)) == sign(f->ddF(a))) {
		x0 = a;
	} else {
		x0 = b;
	}

	// CT sai số 1
	x = x0;
	count = 0;
	if (print_state) {
		print("\t1. Sai số theo công thức mục tiêu\n");
		print_multiple_char('_', 2 * p_precision + 20);
		print("\t|%-12s|%-*s|%-*s|\n", "Lần lặp", p_precision+4, "x", p_precision+6, "Sai số");
		print_multiple_char('-', 2 * p_precision + 20);
	}

	do {
		x = x - f->F(x) / f->dF(x);
		err = f->Err_Target_Form(x, m);
		count++;

		if (print_state) {
			print("\t|%-8d|%*.*lf|%*.*lf|\n", count, p_precision+4, p_precision, x, p_precision+4, p_precision, err);
			print_multiple_char('-', 2 * p_precision + 20);
		}

	} while (count < n);

	// CT sai số 2
	x = x0;
	count = 0;
	if (print_state) {
		print("\t1. Sai số theo công thức hai xấp xỉ liên tiếp\n");
		print_multiple_char('_', 2 * p_precision + 20);
		print("\t|%-12s|%-*s|%-*s|\n", "Lần lặp", p_precision+4, "x", p_precision+6, "Sai số");
		print_multiple_char('-', 2 * p_precision + 20);
	}

	do {
		px = x;
		x = x - f->F(x) / f->dF(x);
		err = f->Err_DA_Form(x, px, m, M);
		count++;

		if (print_state) {
			print("\t|%-8d|%*.*lf|%*.*lf|\n", count, p_precision+4, p_precision, x, p_precision+4, p_precision, err);
			print_multiple_char('-', 2 * p_precision + 20);
		}

	} while (count < n);

	return x;
}

double Newton_Raphson_Err_Formula(Polynomial* f, double a, double b, double e, bool print_state) {
	double x, x0;
	double px = 0;
	int count = 0;
	double m = min( fabs(f->dF(a)), fabs(f->dF(b)) );
	double M = max( fabs(f->ddF(a)), fabs(f->ddF(b)) );
	double err;

	// Chọn điểm Fourier
	if (sign(f->F(a)) == sign(f->ddF(a))) {
		x0 = a;
	} else {
		x0 = b;
	}

	// CT sai số 1
	x = x0;
	count = 0;
	if (print_state) {
		print("\t1. Sai số theo công thức mục tiêu\n");
		print_multiple_char('_', 2 * p_precision + 20);
		print("\t|%-12s|%-*s|%-*s|\n", "Lần lặp", p_precision+4, "x", p_precision+6, "Sai số");
		print_multiple_char('-', 2 * p_precision + 20);
	}

	do {
		x = x - f->F(x) / f->dF(x);
		err = f->Err_Target_Form(x, m);
		count++;

		if (print_state) {
			print("\t|%-8d|%*.*lf|%*.*lf|\n", count, p_precision+4, p_precision, x, p_precision+4, p_precision, err);
			print_multiple_char('-', 2 * p_precision + 20);
		}

	} while (err > e);

	// CT sai số 2
	x = x0;
	count = 0;
	if (print_state) {
		print("\t1. Sai số theo công thức hai xấp xỉ liên tiếp\n");
		print_multiple_char('_', 2 * p_precision + 20);
		print("\t|%-12s|%-*s|%-*s|\n", "Lần lặp", p_precision+4, "x", p_precision+6, "Sai số");
		print_multiple_char('-', 2 * p_precision + 20);
	}

	do {
		px = x;
		x = x - f->F(x) / f->dF(x);
		err = f->Err_DA_Form(x, px, m, M);
		count++;

		if (print_state) {
			print("\t|%-8d|%*.*lf|%*.*lf|\n", count, p_precision+4, p_precision, x, p_precision+4, p_precision, err);
			print_multiple_char('-', 2 * p_precision + 20);
		}

	} while (err > e);

	return x;
}


double Newton_Raphson(Polynomial* f, double a, double b, double e, bool print_state) {
	double x, x0;
	double px = 0;
	int count = 0;

	// Chọn điểm Fourier
	if (sign(f->F(a)) == sign(f->ddF(a))) {
		x0 = a;
	} else {
		x0 = b;
	}

	x = x0;
	
	if (print_state) {
		print_multiple_char('_', 2 * p_precision + 20);
		print("\t|%-12s|%-*s|%-*s|\n", "Lần lặp", p_precision+4, "x", p_precision+6, "Sai số");
		print_multiple_char('-', 2 * p_precision + 20);
	}

	do {
		px = x;
		x = x - f->F(x) / f->dF(x);
		count++;

		if (print_state) {
			print("\t|%-8d|%*.*lf|%*.*lf|\n", count, p_precision+4, p_precision, x, p_precision+4, p_precision, fabs(x - px));
			print_multiple_char('-', 2 * p_precision + 20);
		}

	} while (fabs(x - px) > e);

	return x;
}

// ============================
// Khai triển Các hàm phụ trợ
// ============================

int sign(double x) {
	return x < 0 ? 0 : 1;
}

double min(double a, double b) {
	return a < b ? a : b;
}
double max(double a, double b) {
	return a > b ? a : b;
}

Interval Read_Interval() {
	Interval res;
	double a, b;

	scanf("%lf %lf", &a, &b);
	if (a > b) {
		double t = a;
		a = b;
		b = t;
	}
	res.left = a;
	res.right = b;

	return res;
}

Interval Bisection(Polynomial* f, double a, double b, double dist) {
	Interval res;
	double c = 0;
	while (fabs(a - b) > dist) {
		c = (a + b) / 2;
		if ( sign(f->F(c)) == sign(f->F(b)) )
			b = c;
		else
			a = c;
	}

	res.left = a;
	res.right = b;

	return res;
}

void Bisection(Polynomial* f, Interval* interval, double dist) {
	*interval = Bisection(f, interval->left, interval->right, dist); 
}

#endif