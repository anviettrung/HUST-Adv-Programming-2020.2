#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include "adv_print.h"

using namespace std;

#define EPSILON 0.001
#define TOL 0.001 // Stand for tolerance

typedef struct Interval {
	double left;
	double right;

	Interval(double l = 0, double r = 0) {
		left = l;
		right = r;
	}
} Interval;

typedef struct PNode {
	double coeff;
	int exponent;

	PNode* next;
} PNode;

class Polynomial {
private:
	PNode* head;
	Interval root_interval; // Miền chứa nghiệm
	double* extrema;

public:
	Polynomial() { head = NULL; }
	~Polynomial() {
		PNode* cur = head;

		while (cur != NULL) {
			head = head->next;
			delete cur;
			cur = head;
		}
	}

	void Insert_Node(int c, int e) {
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
	}

	void Print() {
		PNode* cur = head;

		while (cur != NULL) {
			if (cur != head) // not first node
				cout << " + ";
			cout << cur->coeff;

			switch (cur->exponent) {
				case 0: break;

				case 1: 
					cout << "x";
				break;

				default:
					cout << "x^" << cur->exponent; 
				break;
			}

			cur = cur->next;
		}
		cout << endl;
	}

	// Get_Func_Value
	double F(double x) {
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

	// Get_Derivative_Value
	double dF(double x) {
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

	// Change f(x) to f(-x)
	void Reverse_Odd_Exponent_Sign() {
		PNode* cur = head;
		while (cur != NULL) {
			if (cur->exponent % 2 == 1)
				cur->coeff = -cur->coeff;
			cur = cur->next;
		}
	}


	// Tìm cận trên
	double Find_Root_Interval_Upper_Edge() {
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

	void Find_Root_Interval() {
		root_interval.right = Find_Root_Interval_Upper_Edge();

		// Temporary change f(x) to f(-x)
		Reverse_Odd_Exponent_Sign();

		root_interval.left = -Find_Root_Interval_Upper_Edge();

		// Change back to f(x)
		Reverse_Odd_Exponent_Sign();
	}

	void Print_Root_Interval() {
		printf("(%.5f,%.5f)", root_interval.left, root_interval.right);
	}
};

int sign(double x) {
	return x < 0 ? 0 : 1;
}

double Newton_Raphson(Polynomial* f, double x) {
	double h = f->F(x) / f->dF(x);

	while (fabs(h) >= EPSILON) {
		h = f->F(x) / f->dF(x);
		x = x - h;
	}

	return x;
}

double Newton_Raphson(Polynomial* f, double a, double b, int n) {
	return 0;
}

double Newton_Raphson(Polynomial* f, double a, double b, double e) {
	return 0;
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



int main()
{
	Polynomial f;

	f.Insert_Node(3, 0);
	f.Insert_Node(-5, 1);
	f.Insert_Node(-7, 2);
	f.Insert_Node(-4, 3);
	f.Insert_Node(1, 4);

	// f.Insert_Node(3, 0);
	// f.Insert_Node(5, 1);
	// f.Insert_Node(7, 2);
	// f.Insert_Node(4, 3);
	// f.Insert_Node(1, 4);

	f.Print();

	cout.precision(3);

	f.Find_Root_Interval();
	f.Print_Root_Interval();
	cout << endl;

	Interval res = Bisection(&f, 0, 2.5f, 0.5f);
	cout << res.left << " " << res.right << endl;

	// cout << f.dF(2) << endl;
 	//cout << "The value of the root is : " << Newton_Raphson(&f, -20) << endl;

	return 0;
}