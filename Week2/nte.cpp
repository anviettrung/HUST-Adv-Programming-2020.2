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

// ============================
// SYSTEM CALL
// ============================

void ScrollScreen();
void CursorToHome();
void ClearScreen();
char GetInput();
string avtGetCurrentTime();

// ============================
// LAYOUT
// ============================

void MainMenu_Layout();
void Alphabet_Table_Layout();
void PrimeNumberFinder_Layout();
void GCD_HCF_Calculator_Layout();
void ASCII_Art_Layout();
void MagicDonut_Layout(int totalFrame);
void Log_Layout();

// ============================
// CONST
// ============================
const string art_lib_db_file_path = "art-lib-db.dat";
const string art_lib_folder_path = "art-lib/";
const string log_file_path = "nte-activity.log";

// ============================
// Log
// ============================
fstream log_file;
map<char, string> log_activity_name;
const int log_recent_n = 5;

void Init_Log() {
	log_activity_name['s'] = "Open PROGRAM";
	log_activity_name['0'] = "Return to Main Menu.";
	log_activity_name['1'] = "Print Alphabet Table";
	log_activity_name['2'] = "Find Prime Numbers";
	log_activity_name['3'] = "Calculate GCD & HCF";
	log_activity_name['4'] = "View ASCII Art Library";
	log_activity_name['5'] = "Watch Magic Donut";
	log_activity_name['o'] = "View Log File";
	log_activity_name['x'] = "Exit PROGRAM";


	log_file.open(log_file_path, fstream::app); 
}
void End_Log() { log_file.close(); }
void Write_Log(char cmd_code);

// ============================
// MAIN PROGRAM
// ============================
int main()
{
	ScrollScreen();

	Init_Log();
	Write_Log('s');

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
			// case 'o':
			// 	Log_Layout();
			// 	break;
		}
		ans = GetInput();
		Write_Log(ans);
	}

	End_Log();

	ClearScreen();
	return 0;
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

string avtGetCurrentTime() 
{
	time_t now = time(0);
	return ctime(&now);
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

// ----------------------------------------------------
void Log_Layout()
{
	ClearScreen();
	cout << "=== Activity Log ===" << endl;
	cout << log_recent_n << " recent activities:" << endl;
}

void Write_Log(char cmd_code)
{
	if (log_activity_name.find(cmd_code) != log_activity_name.end())
		log_file << avtGetCurrentTime() << "   " << log_activity_name[cmd_code] << endl;
}


