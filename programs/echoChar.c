/* echo.c -- repeats input */

#include <stdio.h>

int main(void) {
	char ch;

	while ((ch = getchar()) != EOF) {
		putchar(ch);
	}

	return 0;
}
