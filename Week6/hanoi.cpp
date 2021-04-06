#include <iostream>
#include <fstream>
#include <unistd.h>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

using namespace std;
// ============================
// GLOBAL
// ============================
#define FRAME_TIME 0.1f
int n = 3;
int *a, *b, *c;

// ============================
// RENDERER
// ============================
void PrintBar(char c, int n);
void PrintTowerRow(int n, int k);
void PrintRow(int n, int a, int b, int c);
void Render();
// ============================
// SYSTEM CALL
// ============================
void ScrollScreen();
void CursorToHome();
void ClearScreen();

void Transfer(int value, int* from, int* to) 
{
	int i = 1;
	while (from[i] == 0 && i < n)
		i++;
	from[i] = 0;

	i = 1;
	while (to[i+1] == 0 && i < n)
		i++;
	to[i] = value;
}

void SolveHanoiTower(int m, int* from, int* to, int* mid)
{
	if (m == 1) {
		//cout << "Disk 1: " << from << "->" << to << endl;
		Transfer(1, from, to);
		Render();
		return;
	}

	SolveHanoiTower(m-1, from, mid, to);
	//cout << "Disk " << n << ": " << from << "->" << to << endl;
	Transfer(m, from, to);
	Render();
	SolveHanoiTower(m-1, mid, to, from);
}

int main()
{
	cin >> n;

	// Init
	a = new int[n+1];
	b = new int[n+1];
	c = new int[n+1];

	for (int i = 0; i < n+1; i++) {
		a[i] = i;
		b[i] = c[i] = 0;
	}

	ScrollScreen();
	Render();
	SolveHanoiTower(n, a, b, c);

	return 0;
}

void PrintBar(char c, int n)
{
	for (int i = 0; i < n; i++)
		cout << c;
}

void PrintTowerRow(int n, int k) 
{
	if (k == 0) {
		PrintBar(' ', n+1);
		cout << "|";
		PrintBar(' ', n);
	} else {
		PrintBar(' ', n-k+1);
		PrintBar(k % 2 == 0 ? '#' : '@', 2*k+1);;
		PrintBar(' ', n-k);
	}
}

void PrintRow(int n, int a, int b, int c)
{
	PrintTowerRow(n, a);
	PrintTowerRow(n, b);
	PrintTowerRow(n, c);
	cout << endl;
}

void Render() 
{
	usleep(FRAME_TIME * 1000000); // 0.3 sec
	ClearScreen();
	for (int k = 0; k < n+1; k++) {
		PrintRow(n, a[k], b[k], c[k]);
	}
	PrintBar('-', 6*n + 7);
	cout << endl;
}

// ============================
// SYSTEM CALL IMPLEMENT
// ============================
void ScrollScreen() 
{ 
	#ifdef _WIN32
		system("clear");
	#else
		cout << "\x1b[2J"; 
	#endif
};
void CursorToHome() 
{
	#ifdef _WIN32
		COORD p = {0, 0};
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p);
	#else
		cout << "\x1b[H";
	#endif 
}

void ClearScreen()
{
	CursorToHome();

	int lines = 26;
	for(int i = 0; i <= lines * 80; i++) {
		putchar(i % 80 ? ' ' : 10); // 10 = [Line Feed]
	}

	CursorToHome();
}