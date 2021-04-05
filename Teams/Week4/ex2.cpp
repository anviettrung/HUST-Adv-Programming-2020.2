#include <iostream>

using namespace std;

char RevertChar(char c)
{
	if ('a' <= c && c <= 'z')
		c = c + 'A' - 'a';
	else if ('A' <= c && c <= 'Z')
		c = c + 'a' - 'A';

	return c;
}

int main()
{
	string str;

	cout << "String to convert: " << endl;
	cin >> str;

	for (int i = 0; i < str.length(); i++)
		cout << RevertChar(str[i]);

	cout << endl;

	return 0;
}