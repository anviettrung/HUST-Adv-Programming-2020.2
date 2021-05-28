#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream inp("SFile.txt");
	ofstream out("DFile.txt");
	string line;

	if (!inp || !out) return 0;

	while (getline(inp, line, '\0'))
		out << line;

	inp.close();
	out.close();

	return 0;
}