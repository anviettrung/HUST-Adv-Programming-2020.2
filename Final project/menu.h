#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <ctime>
#include <map>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

using namespace std;

// ============================
// CONSTANT & DEFINITION
// ============================
#define DEFAULT_SCREEN_WIDTH  80
#define DEFAULT_SCREEN_HEIGHT 24

typedef void (*Layout)();

// ============================
// SYSTEM CALL
// ============================

void ScrollScreen();
void CursorToHome();
void ClearScreen(int row, int col);
char GetInput();

// ============================
// MENU
// ============================
class Menu 
{
private:
	int layout_count;
	Layout* layout;

	int screen_w;
	int screen_h;

public:
	Menu(int count, Layout* lays) {
		layout_count = count;
		layout = lays;
	}

	void Print() {
		for (int i = 0; i < layout_count; i++)
			layout[i]();
	}
};


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

void ClearScreen(int row, int col)
{
	CursorToHome();

	for(int i = 0; i <= row * col; i++) {
		putchar(i % col ? ' ' : 10); // 10 = [Line Feed]
	}

	CursorToHome();
}

char GetInput()
{
	#ifdef _WIN32
		char input = getch();
	#else
		// Set terminal to raw mode 
		system("stty raw"); 
		// Wait for single character 
		char input = getchar(); 
		// Reset terminal to normal "cooked" mode 
		system("stty cooked"); 
	#endif 

	return input;
}


