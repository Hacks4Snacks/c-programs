/* guess.c -- a number-guesser */
#include <stdio.h>

int main(void) {
	int upperBound = 100;
	int lowerBound = 0;
	int guess;
	char response;
	guess = 50;

	printf("Pick an integer from 1 to 100. I will try to guess ");
	printf("it.\nRespond with a y if my guess is right and with");
	printf("\na h if it is too high and a l if it is too low.\n");
	printf("Uh...is your number %d\n", guess);

        while ((response = getchar()) != 'y') {
		while (getchar() != '\n') { //clear input
		       continue;
		}
	        if (response == 'h') {
	               upperBound = guess;	       
	       }
	        else if (response == 'l') {
		       lowerBound = guess;
	       }
	        else {
		       printf("Invalid input. Try again.\n");
		       continue;
		}
	       guess = (upperBound + lowerBound) / 2.0;
	       printf("Well, then, is it %d?\n", guess);
	}
	printf("I knew I could do it!\n");
	return 0;
}
