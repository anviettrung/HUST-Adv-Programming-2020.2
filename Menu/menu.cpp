#include <iostream>
#include <string>
#include "ConsoleRenderer.h"

using namespace std;
using namespace csr;

void AF_OpenFile();
void AF_SaveFile();

int main(int argc, char const *argv[])
{
	const int AF_menu_bar_count = 2; // app funcs on menu bar count
	AppFunc main_AF_list[AF_menu_bar_count] = {
	{
		.funcName = "Open File",
		.func     = AF_OpenFile
	},
	{
		.funcName = "Save File",
		.func     = AF_SaveFile
	},
	};

	DoMainLoop(AF_menu_bar_count, main_AF_list);

	return 0;
}

void AF_OpenFile()
{

}

void AF_SaveFile()
{

}