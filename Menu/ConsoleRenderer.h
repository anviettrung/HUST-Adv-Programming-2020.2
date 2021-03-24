// "csr" stand for "ConSole Renderer"
namespace csr {

#include <iostream>
#include <string>
// #include <math.h>
// #include <unistd.h>
// #include <ctime>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

#define APP_SCREEN_WIDTH   80
#define APP_SCREEN_HEIGHT  24
#define APP_SCREEN_LENGTH  APP_SCREEN_WIDTH * APP_SCREEN_HEIGHT

#define KEY_ESC   27
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80


char* screen = new char[APP_SCREEN_LENGTH];

struct AppFunc {
	std::string funcName;
	void (*func)();
};

// ============================
// SYSTEM CALL
// ============================

void ScrollScreen();
void CursorToHome();
void ClearScreen();
char GetInput();

std::ostream& bold_on(std::ostream& os);
std::ostream& bold_off(std::ostream& os);

// ============================
// RENDERING
// ============================
void Render();
void DrawText(std::string text, int x, int y);
void DrawMenuBar(int app_func_count, AppFunc app_funcs[]);

// ============================
// MAIN LOOP
// ============================
bool ProcessInput(char input_key);
void DoMainLoop(int app_func_count, AppFunc app_funcs[])
{
	ScrollScreen();
	ClearScreen();
	DrawMenuBar(app_func_count, app_funcs);

	char input_key = '0';
	while (input_key != 'q') {
		Render();
		input_key = GetInput();
		if (ProcessInput(input_key))
			input_key = '0';
	}
}

bool ProcessInput(char input_key)
{
	char ex = '0';
	if (input_key == KEY_ESC) {
		ex = GetInput();
	    switch (ex) {
	        case KEY_UP:
	            std::cout << "up";
	            break;
	        case KEY_DOWN:
	            std::cout << "Down";   // key down
	            break;
	        case KEY_LEFT:
	            std::cout << "Left";  // key left
	            break;
	        case KEY_RIGHT:
	            std::cout << "Right";  // key right
	            break;
	        case 91:
	        	std::cout << "VL";
	        	break;
	        default:
	        	return false;
	            break;
	    } 
	    return true;
	}

    return false;
}

// ============================
// RENDERING IMPLEMENT
// ============================
void Render()
{
	CursorToHome();

	for (int c = 0; c < APP_SCREEN_LENGTH; c++) {
		if (c % APP_SCREEN_WIDTH == 0) putchar(10);
		putchar(screen[c]);
	}

	CursorToHome();
}

void DrawText(std::string text, int x, int y)
{
	int start = y * APP_SCREEN_WIDTH + x;
	for (int i = 0; i < text.length(); i++)
		screen[start + i] = text[i];
}

void DrawMenuBar(int app_func_count, AppFunc app_funcs[])
{
	int x_pos = 0;
	for (int i = 0; i < app_func_count; i++) {
		DrawText(app_funcs[i].funcName, x_pos, 0);
		x_pos += app_funcs[i].funcName.length();
		screen[x_pos + 1] = '|';
		x_pos += 2;
	}
}

// ============================
// SYSTEM CALL IMPLEMENT
// ============================
void ScrollScreen() 
{ 
	#ifdef _WIN32
		system("clear");
	#else
		std::cout << "\x1b[2J"; 
	#endif
};
void CursorToHome() 
{
	#ifdef _WIN32
		COORD p = {0, 0};
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p);
	#else
		std::cout << "\x1b[H";
	#endif 
}

void ClearScreen()
{
	memset(screen, ' ', APP_SCREEN_LENGTH);
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

std::ostream& bold_on(std::ostream& os)
{
    return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
    return os << "\e[0m";
}

}