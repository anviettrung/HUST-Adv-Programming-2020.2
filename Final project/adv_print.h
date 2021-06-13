#ifndef ADV_PRINT
#define ADV_PRINT

#include <stdio.h>
#include <stdarg.h>
#include "system.h"

#define MAX_N 256

namespace adv_print {
// ============================
// Khai báo
// ============================
	// FILE output
	static FILE * fout = NULL;

	// Mở file
	void init_output_file(char * fileName, const char * mode);
	// Đóng file
	void close_output_file();

	// In ra màn hình và file (nếu có)
	void print(const char* format, ...);

	// In kí tự 'c' n lần ra màn hình và file (nếu có)
	void print_multiple_char(char c, int n);

	// In thời gian và mệnh lệnh ra màn hình và file (nếu có)
	void print_command(const char* command);

// ============================
// Khai triển
// ============================

	void init_output_file(char * fileName, const char * mode) {
		fileName[strcspn(fileName, "\n")] = 0; // remove '\n' character
		fout = fopen(fileName, mode);
	}

	void close_output_file() {
		fclose(fout);
	}

	void print(const char* format, ...) {
		va_list args;

		va_start(args, format);
		vprintf(format, args);
		va_end(args);

		if (fout != NULL) {
			va_start(args, format);
			vfprintf(fout, format, args);
			va_end(args);
		}
	}

	void print_multiple_char(char c, int n) {
		char s[MAX_N];
    	memset(s, c, n);
    	s[n] = 0;

		printf("\t%s\n", s);

		if (fout != NULL)
			fprintf(fout, "\t%s\n", s);
	}

	void print_command(const char* command) {
		printf("=== %s ===\n", command);

		if (fout != NULL)
			fprintf(fout, "%s\t%s\n", avt_sys::GetCurrentTime(), command);
	}
}

#endif