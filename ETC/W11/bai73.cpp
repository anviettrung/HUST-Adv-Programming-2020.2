#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream inp("SFile.txt");
	bool spacing = true;
	int word_count = 0;
	string line;
	char ascii = '\0';

	if (!inp) return 0;

	while (getline(inp, line, '\0')) {
		for (int i = 0; i < line.length(); i++) {
			ascii = line[i];
			if (ascii == ' ') {
				spacing = true;
			} else if (spacing) {
				word_count++;
				spacing = false;
			}
		}
	}

	cout << word_count << endl;

	inp.close();

	return 0;
}