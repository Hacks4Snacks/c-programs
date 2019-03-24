/*paint.c -- users conditional operator*/
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	const int COVERAGE = 350;
	int sqFeet;
	int cans;

	printf("Enter number of square feet to be painted:\n");
	while (scanf("%d", &sqFeet) == true) {
		cans = sqFeet / COVERAGE;
		cans += ((sqFeet % COVERAGE == 0)) ? 0 : 1;
		printf("You need %d %s of paint.\n", cans,
				cans == 1 ? "can" : "cans");
		printf("Enter next value (q to quit):\n");
	}

	return 0;
}
