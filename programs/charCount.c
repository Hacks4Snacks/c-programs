/* countchar.c -- count characters up to EOF */

#include <stdio.h>
#include <ctype.h>

int main(void) {
	int ch;
	int totalCount;
	int upperCount;
	int lowerCount;
	int otherCount;
	
	totalCount = 0;
        upperCount = 0;
	lowerCount = 0;
	otherCount = 0;

	
	//EOF on UNIX/LINUX = CTRL + D
	while((ch = getchar()) != EOF) {
		totalCount++;
		if (isupper(ch)) {
			upperCount++;
		}
		else if (islower(ch)) {
			lowerCount++;
		}
		else {
			otherCount++;
		}
	}
	printf("Total character count: %d\n", totalCount);
	printf("Uppercase letters: %d\n", upperCount);
	printf("Lowercase letters: %d\n", lowerCount);
	printf("Other characters: %d\n", otherCount);

	return 0;
}
