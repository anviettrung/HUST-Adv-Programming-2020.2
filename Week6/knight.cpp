#include <iostream>
#include <fstream>

using namespace std;

#define N 8

int SolveKnightRE(int x, int y, int movei, int sol[N][N], int xMove[], int yMove[]);

void PrintBoard(int sol[N][N], ofstream& out) {
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++)
			out << " " << setw(2) << sol[x][y] << " ";
		out << endl;
	}
}

bool isSafe(int x, int y, int sol[N][N])
{
	return (x >= 0 && x < N && y >= 0 && y < N
		&& sol[x][y] == -1);
}

int SolveKnight(ofstream& out) {
	int sol[N][N];

	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			sol[x][y] = -1;

	int xMove[8] = {  2,  1, -1, -2, -2, -1,  1,  2 };
	int yMove[8] = {  1,  2,  2,  1, -1, -2, -2, -1 };

	sol[0][0] = 0;

	if (SolveKnightRE(0, 0, 1, sol, xMove, yMove) == 0) {
        cout << "Solution does not exist";
        return 0;
	} else
		PrintBoard(sol, out);

	return 1;
}

int SolveKnightRE(int x, int y, int movei, int sol[N][N], int xMove[N], int yMove[N])
{
	int k, next_x, next_y;
	if (movei == N * N)
		return 1;

	for (k = 0; k < 8; k++) {
	    next_x = x + xMove[k];
	    next_y = y + yMove[k];
	    if (isSafe(next_x, next_y, sol)) {
	        sol[next_x][next_y] = movei;
	        if (SolveKnightRE(next_x, next_y, movei + 1, sol, xMove, yMove) == 1)
	        	return 1;
	        else
	           // backtracking
	        	sol[next_x][next_y] = -1;
	    }
	}
	return 0;
}

int main() {
	ofstream out("knight.txt");
	SolveKnight(out);
	out.close();

	return 0;
}