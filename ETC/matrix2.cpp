#include <stdio.h>

#define MAX 100

int main()
{
	int m, n;
	int a[MAX][MAX];
	FILE *inp;
	inp = fopen("matrix_out.txt", "r");

	if (inp != NULL) {
		fscanf(inp, "%d %d", &m, &n);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
				fscanf(inp, "%d", &a[i][j]);
		}

		printf("%d %d\n", m, n);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
				printf("%d ", a[i][j]);
			printf("\n");
		}

		fclose(inp);
	}
}