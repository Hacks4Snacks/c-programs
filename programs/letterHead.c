/* letterHead.c -- prints a simple heading */

#include <stdio.h>
#define NAME "Test, LLC."
#define ADDRESS "1337 street"
#define PLACE "NOVA, 00100"
#define WIDTH 40

void starbar(void); //prototype the function

int main(void) {
	starbar(); //call function
	printf("%s\n", NAME);
	printf("%s\n", ADDRESS);
	printf("%s\n", PLACE);
	starbar(); //call function

	return 0;
}

void starbar(void) { //define starbar function
	int count;

	for (count =1; count <= WIDTH; count++) {
		putchar('*');
	}
	putchar('\n');
}
