
#include <iostream>

using namespace std;

#define LIMIT 1000

int main()
{
	char str[LIMIT];
	char inverse[LIMIT];

	cout << "Type something: ";
	fgets(str, LIMIT, stdin);

	int strlen = 0;
	for (strlen = 0; str[strlen] != '\0'; strlen++);

	// new inverse string
	for (int i = 0; i < strlen; i++)
		inverse[i] = str[strlen - i - 1];

	// inverse old string
	for (int i = 0; i < (strlen / 2); i++) {
		char t = str[i];
		str[i] = str[strlen - i - 1];
		str[strlen - i - 1] = t;
	}

	cout << str << endl;

	return 0;
}