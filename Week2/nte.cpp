#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

// SYSTEM CALL
void ScrollScreen() { cout << "\x1b[2J"; };
void CursorToHome() { cout << "\x1b[H"; }
void ClearScreen();
char GetInput();

// Layout
void MainMenu_Layout();
void Alphabet_Table_Layout();
void MagicDonut_Layout(int totalFrame);

// 

int main()
{
	ScrollScreen();

	char ans = '0';
	while (ans != 'x') {
		switch (ans) {
			case '0':
				MainMenu_Layout();
				break;
			case '1':
				Alphabet_Table_Layout();
				break;
			case '5':
				MagicDonut_Layout(33 * 5); // 5 secs
				break;
		}
		ans = GetInput();
	}
	ClearScreen();

	return 0;
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
  // Set terminal to raw mode 
  system("stty raw"); 

  // Wait for single character 
  char input = getchar(); 

  // Reset terminal to normal "cooked" mode 
  system("stty cooked"); 

  return input;
}

void MainMenu_Layout()
{
	ClearScreen();
	cout << "=== MAIN MENU ===" << endl
		 << "[1] Print Alphabet Table" << endl
		 << "[2] Prime Number" << endl
		 << "[3] GCD" << endl
		 << "[4] Draw Something" << endl
		 << "[5] Magic Donut" << endl
		 << "[x] Exit";
}

void Alphabet_Table_Layout()
{
	ClearScreen();
	cout << "=== Alphabet Table ===" << endl;

	for (char c = 'A'; c <= 'Z'; c++) {
		if ((int)(c-'A') % 10 == 0) {
			cout << endl << "    ";
		}
		cout << c << " ";
	}

	cout << endl << endl
		 << "[0] Back" << endl
		 << "[x] Exit";
}

void PrintProcess(float t)
{
	cout << "Process: [";
	for (int i = 0; i < 50; i++) 
		putchar(i / 49.0f <= t ? '#' : '_');
	
	cout << "]" << endl;
}

void MagicDonut_Layout(int totalFrame)
{
	ClearScreen();

	float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
   	
    for (int frame = 1; frame <= totalFrame; frame++) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        // Render
        CursorToHome();
        cout << "=== Magic Donut ===" << endl;
        PrintProcess((float)frame / totalFrame);

        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        usleep(30000); // 0.03 sec
    }

    cout << "[0] Back" << endl
		 << "[x] Exit";
}

