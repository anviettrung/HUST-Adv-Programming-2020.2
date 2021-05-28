#include <stdio.h>

#define MAX_FLOAT 100

int main()
{
	int n = 0;
	float a[MAX_FLOAT], b[MAX_FLOAT];
	FILE *f, *copy_f;

	f = fopen("float.bin", "wb");

	if (f == NULL) {
		printf("File could not be opened.\n");
	} else {
		printf("Enter number of floats: ");
		scanf("%d", &n);

		printf("Enter list of floats:");
		for (int i = 0; i < n; i++) {
			scanf("%f", &a[i]);
		}

		fwrite(&n, sizeof(int), 1, f);
		fwrite(a, sizeof(float), n, f); 
	}
	fclose(f);

	f = fopen("float.bin", "rb");

	if (f == NULL) {
		printf("File could not be opened.\n");
	} else {
		fread(&n, sizeof(int), 1, f);
		fread(b, sizeof(float), n, f);

		printf("\n");
		for (int i = 0; i < n; i++)
			printf("%.2f ", b[i]);
		printf("\n");
	}
	fclose(f);

	copy_f = fopen("copy_float.bin", "wb");
	if (copy_f == NULL) {
		printf("File could not be opened.\n");
	} else {
		fwrite(&n, sizeof(int), 1, copy_f);
		fwrite(b, sizeof(float), n, copy_f); 
	}
	fclose(copy_f);

	return 0;
}