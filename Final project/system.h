#ifndef AVT_SYSTEM
#define AVT_SYSTEM

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <ctime>
#include <map>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

using namespace std;

namespace avt_sys {

// ============================
// SYSTEM CALL
// ============================
	void ScrollScreen();
	void CursorToHome();
	void ClearScreen();
	char GetInput();
	string avtGetCurrentTime();

// ============================
// IMPLEMENT
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

	char* GetCurrentTime() 
	{
		time_t now = time(0);
		return ctime(&now);
	}
}

#endif