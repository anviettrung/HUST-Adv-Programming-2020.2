#include <stdio.h>

#define MAX 100

int main()
{
	int m, n;
	int a[MAX][MAX];
	FILE *output;
	output = fopen("matrix_out.txt", "w");

	printf("Nhap m = ");
	scanf("%d", &m);

	printf("Nhap n = ");
	scanf("%d", &n);

	for (int i = 0; i < m; i++) {
		printf("Nhap dong thu i: ");
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	}

	fprintf(output, "%d %d\n", m, n);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			fprintf(output, "%d ", a[i][j]);
		fprintf(output, "\n");
	}


	fclose(output);
}