#include <iostream>
#include <string>
#include "menu.h"

using namespace std;

// ============================
// DEFINITION
// ============================
#define PROJECT_SETTINGS_FILE "project-settings.txt"

// ============================
// CONSTANT
// ============================

// ============================
// GLOBAL VARIABLE
// ============================
fstream  ps_file;
ofstream out_file;

// ============================
// DATA TYPE
// ============================


// ============================
// MAIN FUNCTION
// ============================
int Initialization();

// ============================
// MAIN PROGRAM
// ============================
int main()
{
	Initialization();

	return 0;
}

// ============================
// IMPLEMENT
// ============================
int Initialization() 
{
	// OPEN FILE
	ps_file.open(PROJECT_SETTINGS_FILE);


}