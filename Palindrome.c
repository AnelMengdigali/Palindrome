#include <stdio.h>
#include <string.h>

//The function does a saving the data into the output file
void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrIOfileLines) {

	int row;

	FILE *outFile;

	outFile = fopen(fileName, "a");

	if (outFile == NULL) {

		printf("CANNOT open %s\n", fileName);

		return;

	}

	//The each line of subfile (substring) is printed into the output file
	fprintf(outFile, "%s\n", ssData);

	//The array which was filled in the checkSubstringPalindrome function is printed into the output file line by line
	for (row = 0; row < nrIOfileLines; row++) {

		fprintf(outFile, "%s", oStringData[row]);

	}

	fprintf(outFile, "\n");

	fclose(outFile);

}

//The function identify the line of string of infile for having feature of Palindrome
int isPalindrome(char str[]) {

	_Bool result;

	int leftSide = 0;

	int strLength = strlen(str);

	//Checking the string for being a Palindrome
	int rightSide = strLength - 1;

	while (leftSide < (strLength / 2)) {

		if (str[leftSide] != str[rightSide]) {

			result = 0;

			break;
		}

		else {

			result = 1;

		}

		leftSide++;
		rightSide--;

	}

	//Returns the result as integer number 0 or 1 (false or true)
	return result;
}

//The function that calls isPalindrome() function and assigns string to the returned result
char *getPalindrome(char str[]) {

	char *result;

	if (isPalindrome(str) == 1) {

		result = "Is_Palindrome";

	}

	else {

		result = "Not_Palidrome";

	}

	//Returns result as constant string
	return result;

}

//The function that counts the occurrence of substring in infile's line if string
int howManySubstrings(char subStr[], char str[]) {

	int count = 0;

	//Identifying the length of the string, until a null character (subsequently, the same operation will do this kind of code)
	int subLength = strlen(subStr);
	int strLength = strlen(str);

	int subIndex = 0;
	int strIndex;

	//Counting the occurrences of appearance of substring in the infile string
	for (strIndex = 0; strIndex <= strLength; strIndex++) {

		if (subIndex == subLength) {

			count++;
			subIndex = 0;

		}

		if (str[strIndex] == subStr[subIndex]) {

			subIndex++;

		}

		else {

			subIndex = 0;

		}

	}

	//Returns result as integers
	return count;

}

/*
 * The function which identify number of substrings in the infile strings and their ability of being Palindrome word
 * by calling two individual functions,
 * then stores returned results in output array of chars
 */
void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines) {

	int numSubStr;
	char *resultPaldr;

	int row;

	for (row = 0; row < nrIOfileLines; row++) {

		numSubStr = howManySubstrings(subStr, iStringData[row]);

		resultPaldr = getPalindrome(iStringData[row]);

		sprintf(oStringData[row], "%s\t%i\t%s\n", iStringData[row], numSubStr, resultPaldr);

	}

}

//The function that reads two input file separately and stores their data into 2d array of chars
void readFile(char filename[], char twoDimArr[][50]) {

	int row = 0;
	int column;

	char filestring[50];

	FILE *inFile;

	inFile = fopen(filename, "r");

	if (inFile == NULL) {

		printf("CANNOT open %s\n", filename);

		return;

	}

	//Store data until the end of line
	while (fgets(filestring, 50, inFile) != NULL) {

		for (column = 0; column < 50; column++) {

			//Eliminate characters of new lines so that they will not affect subsequent output
			if (filestring[column] == '\n' || filestring[column] == '\r') {

				twoDimArr[row][column] = '\0';

				break;

			}

			else {

				twoDimArr[row][column] = filestring[column];

			}

		}

		row++;

	}

	fclose(inFile);

}

//The function counts number of lines of the two input files
int countFileLines(char filename[]) {

	int line = 0;

	char filechar;

	FILE *infile;

	infile = fopen(filename, "r");

	if (infile == NULL) {

		printf("CANNOT open %s\n", filename);

		return 1;

	}

	//Reading the first character from a file to start while loop (subsequently, the same operation will do this kind of code)
	filechar = fgetc(infile);

	//Working with the file until the end of it
	while (filechar != EOF) {

		if (filechar == '\n') {

			line++;

		}

		//Similarly, the characters from the file goes one by one (subsequently, the same operation will do this kind of code)
		filechar = fgetc(infile);

	}

	fclose(infile);

	//Returns result as integers
	return line;

}

//Starting point of the program
int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	char infile[] = "iStrings.txt";
	char outfile[] = "oStrings.txt";
	char subfile[] = "subStrings.txt";

	/*
	 * Calling a function that reads the input file called iStrings.txt,
	 * and counts number of lines in it
	 * and returns result which is stored as row numbers of an input string array
	 * then of the output array
	 */
	int ifNumLines = countFileLines(infile);
	char iStringData[ifNumLines][50];

	/*
	 * This codes do the same as above, but here it reads the input file called subStrings.txt,
	 * and saves result as row of substring array
	 */
	int subfNumLines = countFileLines(subfile);
	char subArr[subfNumLines][50];

	char oStringData[ifNumLines][50];

	int row = 0;

	//Calling a function that reads the data from the iStrings.txt (infile) and saves everything in 2D array
	readFile(infile, iStringData);

	//Calling a function that reads the data from the subStrings.txt (subfile) and saves everything in 2D array
	readFile(subfile, subArr);

	/*
	 * Opening and checking for validity a file (subsequently, the same operation will do this kind of code)
	 * for writing purpose which allow us to clear everything in output file before a new start
	 */
	FILE *outFile;

	outFile = fopen(outfile, "w");

	if (outFile == NULL) {

		printf("CANNOT open %s\n", outfile);

		return 1;

	}

	//Closing the file as the work is done (subsequently, the same operation will do this kind of code)
	fclose(outFile);

	//The following lines of code will operate until the data from subfile ends
	while (row < subfNumLines) {

		/*
		 * Calling a function that checks strings from infile for having how many substrings
		 * and for being a Palindrome
		 * and stores the results in output 2D array of chars
		 */
		checkSubstringPalindrome(subArr[row], iStringData, oStringData, ifNumLines);

		//Calling a function that writes the insides of the output 2D array into output file
		writeFile(outfile, subArr[row], oStringData, ifNumLines);

		row++;

	}

	return 0;
}

