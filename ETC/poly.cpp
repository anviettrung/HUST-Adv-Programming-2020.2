#include <iostream>

using namespace std;

struct Term {
	int a;
	Term* prev;
	Term* next;
};

Term* AddPolynomial(Term* a, Term* b)
{
	Term* pa = a;
	Term* pb = b;
	Term* res = new Term();
	Term* pres = res;

	while (pa != NULL && pb != NULL) {
		(*pres).a = (*pa).a + (*pb).a;
		pa = pa->next;
		pb = pb->next;

		if (pa != NULL && pb != NULL) {
			pres->next = new Term();
			pres->next->prev = pres;
			pres = pres->next;
		}
	}

	while (pa != NULL) {
		pres->next = new Term();
		pres->next->prev = pres;
		pres = pres->next;

		(*pres).a = (*pa).a;
		pa = pa->next;
	}

	while (pb != NULL) {
		pres->next = new Term();
		pres->next->prev = pres;
		pres = pres->next;

		(*pres).a = (*pb).a;
		pb = pb->next;
	}

	return res;
}

Term* MultiPolynomial(Term* a, Term* b)
{
	Term* pa = a;
	Term* pb = b;
	Term* res = new Term();
	Term* pres = res;
	Term* first = res;

	while (pb != NULL) {
		pa = a;
		pres = first;
		while (pa != NULL) {
			(*pres).a += (*pa).a * (*pb).a;

			pa = pa->next;

			if (pa != NULL && pres->next == NULL) {
				pres->next = new Term();
				pres->next->prev = pres;
				pres = pres->next;
				(*pres).a = 0;
			} else {
				pres = pres->next;
			}
		}

		pb = pb->next;

		if (pb != NULL && first->next == NULL) {
			first->next = new Term();
			first->next->prev = first;
			first->next->a = 0;
		}
		first = first->next;
	}

	return res;
}

void Print(Term* t)
{
	Term* p = t;
	while (p != NULL) {
		cout << (*p).a << " ";
		p = p->next;
	}	
}

int main()
{
	Term *a = new Term(), *b = new Term();
	int n = 0;
	Term* p;

	cout << "an = ";
	cin >> n;

	p = a;
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			p->next = new Term();
			p->next->prev = p;
			p = p->next;
		}
		cin >> (*p).a;
	}

	cout << "bn = ";
	cin >> n;
	p = b;
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			p->next = new Term();
			p->next->prev = p;
			p = p->next;
		}
		cin >> (*p).a;
	}

	cout << "a + b = ";
	Print(AddPolynomial(a, b));
	cout << endl;

	cout << "a * b = ";
	Print(MultiPolynomial(a, b));
	cout << endl;

	return 0;
}