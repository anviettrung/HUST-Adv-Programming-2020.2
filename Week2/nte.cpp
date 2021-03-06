#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

// ============================
// SYSTEM CALL
// ============================

void ScrollScreen() { cout << "\x1b[2J"; };
void CursorToHome() { cout << "\x1b[H"; }
void ClearScreen();
char GetInput();

// ============================
// LAYOUT
// ============================

void MainMenu_Layout();
void Alphabet_Table_Layout();
void PrimeNumberFinder_Layout();
void GCD_HCF_Calculator_Layout();
void ASCII_Art_Layout();
void MagicDonut_Layout(int totalFrame);

// ============================
// CONST
// ============================
const string art_lib_db_file_path = "art-lib-db.dat";
const string art_lib_folder_path = "art-lib/";


// ============================
// MAIN PROGRAM
// ============================
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
			case '2':
				PrimeNumberFinder_Layout();
				break;
			case '3':
				GCD_HCF_Calculator_Layout();
				break;
			case '4':
				ASCII_Art_Layout();
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
// ============================
// SYSTEM CALL IMPLEMENT
// ============================

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

// ============================
// LAYOUT IMPLEMENT
// ============================

// ----------------------------------------------------
void MainMenu_Layout()
{
	ClearScreen();
	cout << "=== MAIN MENU ===" << endl
		 << "[1] Print Alphabet Table" << endl
		 << "[2] Find Prime Number In Range" << endl
		 << "[3] GCD & HCF Calculator" << endl
		 << "[4] ASCII Art Library" << endl
		 << "[5] Magic Donut" << endl
		 << "[x] Exit";
}

// ----------------------------------------------------
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

// ----------------------------------------------------
bool IsPrime(long n) {
	if (n < 2)
		return false;

	for (long i = 2; i <= sqrt(n); i++)
		if (n % i == 0) return false;

	return true;
}

void PrimeNumberFinder_Layout()
{
	ClearScreen();
	cout << "=== Prime Number Finder ===" << endl
		 << "Enter finding range (a, b)." << endl;

	long a, b;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	cout << "Prime numbers in range (" << a << "," << b << "):" << endl;

	int counter = 0;
	for (long k = a; k <= b; k++) {
		if (IsPrime(k)) {
			cout << k << endl;
			counter++;
			usleep(100000);
		}
	}

	cout << "There are " << counter << " prime numbers!" << endl
		 << "[0] Back" << endl
		 << "[x] Exit";
}

// ----------------------------------------------------
long gcd(long a, long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b); 
}

long hcf(long a, long b)
{
	return a * b / gcd(a, b);
}

void GCD_HCF_Calculator_Layout()
{
	ClearScreen();
	cout << "=== GCD-HCF Calculator ===" << endl
		 << "Enter 2 numbers to calculate (a, b)." << endl;

	long a, b;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	cout << endl
		 << "    GCD(" << a << "," << b << ") = " << gcd(a, b) << endl
		 << "    HCF(" << a << "," << b << ") = " << hcf(a, b) << endl << endl;

	cout << "[0] Back" << endl
		 << "[x] Exit";
}

// ----------------------------------------------------
void ASCII_Art_Layout()
{
	ClearScreen();
	cout << "=== ASCII Art Library ===" << endl;

	string art_name;
	ifstream art_lib_db_file(art_lib_db_file_path);

	int art_counter = 0;
	while (getline(art_lib_db_file, art_name)) {
		if (art_counter % 3 == 0)
			cout << endl << "    ";
		art_counter++;

		cout << art_name << "   ";
	}

	art_lib_db_file.close();

	string art_select_name;
	cout << endl << endl
		 << "Show Art: ";

	cin >> art_select_name;

	string art_render_line;
	ifstream art_file(art_lib_folder_path + art_select_name + ".dat");
	if (art_file) {
		ClearScreen();
		cout << "=== " + art_select_name + " ===" << endl;

		// Drawing
		while (getline(art_file, art_render_line))
			cout << art_render_line << endl;
	} else {
		cout << "Sorry, art named \"" + art_select_name + "\" doesn't exist!" << endl;
	}
	art_file.close();

	cout << "[0] Back" << endl
		 << "[x] Exit";
}

// ----------------------------------------------------
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

