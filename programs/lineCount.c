#include <stdio.h>

/* C program to count the number of lines in a text file. */


#define MAX_FILE_NAME 100

int main() {
	FILE *file;
	int count; //used to count the lines
	char filename[MAX_FILE_NAME]; //constant array of characters declared above the int function
	char c; //used to store a character read from file

	/*Get the file name from the user.
	 * name is acceptable if in current folder
	 * otherwise will need full path*/

	printf("Enter file name: ");
	scanf("%s", filename);
	

	//Open the file
	file = fopen(filename, "r");

	//Check if file exists
	if (file == NULL) {
		printf("ERROR! Could not open requested file: %s.\n", filename);
		return 1;
	}

	//Extract characters from file and store in character c
	for (c = getc(file); c != EOF; c = getc(file))
		if (c == '\n') {
			count = count + 1;
		} //Increment count if character is new line

	//Close the file
	fclose(file);
	printf("The file %s has %d lines.\n", filename, count);

	return 0;
}

