#include <iostream>
#include <fstream>

using namespace std;

void PrintBoard(int* board, int n, ofstream& out) {
	out << endl;
	char* t = new char[n];
	for (int i = 0; i < n; i++)
		t[i] = '0';

	for (int i = 0; i < n; i++) {
		t[board[i]] = '1';
		out << t << endl;
		t[board[i]] = '0';
	}
}

bool isSafe(int* board, int n, int row, int col)
{
	for (int i = 0; i < row; i++)
		if (board[i] == col || abs(col - board[i]) == abs(row - i))
			return false;

	return true;
}

void SolveNQ(int* board, int n, int row, ofstream& out)
{
	if (row == n) {
		PrintBoard(board, n, out);
		return;
	}

	for (int i = 0; i < n; i++) {
		if (isSafe(board, n, row, i)) {
			board[row] = i;
			SolveNQ(board, n, row+1, out);
		}
	}
}

void SolveQueen(int n, ofstream& out) {
	int* a = new int[n];
	SolveNQ(a, n, 0, out);
}


int main() {
	int n = 0;
	cout << "N = ";
	cin >> n;

	ofstream out("queen.txt");
	SolveQueen(n, out);
	out.close();

	return 0;
}