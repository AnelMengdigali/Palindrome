#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//A declaration of a new struct type
typedef struct _Node {

	char strData[50];

	struct _Node *next;

} Node;

//The function that does a saving the data into the output file
void writeFile2(char fileName[], char ssData[], Node **oLinkedList) {

	FILE *outFile;

	outFile = fopen(fileName, "a");

	if (outFile == NULL) {

		printf("CANNOT open %s\n", fileName);

		return;

	}

	//The each line of subfile (substring) is printed into the output file
	fprintf(outFile, "%s\n", ssData);

	//Skipping the first node because it is the head of LinkedList and stores nothing in strData
	oLinkedList = &((**oLinkedList).next);

	//The linked list which was filled in the checkSubstringPalindrome function is printed into the output file
	while ((*oLinkedList) != NULL) {

		fprintf(outFile, "%s", (**oLinkedList).strData);

		oLinkedList = &((**oLinkedList).next);

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

//The function that counts the occurrence of substring in infile's line of string
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

//A function that does freeing of the allocated memory
void freeLinkedlist(Node *head) {

	if (head != NULL) {

		freeLinkedlist((*head).next);

		free(head);

	}

}

//A function that prints the insides of linked list
void printLinkedlist(Node *head) {

	Node *temp = head;

	if (head != NULL) {

		printf("%s", (*temp).strData);

		printLinkedlist((*temp).next);

	}
}

//Appending the Node to the end of the oLinkedList
void appendNode(Node **oLinkedList, char outputLine[]) {

	int row;

	if ((**oLinkedList).next == NULL) {

		Node* lastNode = (Node*) malloc(sizeof(Node));

		for (row = 0; row < strlen(outputLine); row++) {

			(*lastNode).strData[row] = outputLine[row];

		}

		(*lastNode).strData[row] = '\0';

		(*lastNode).next = NULL;

		(**oLinkedList).next = lastNode;

	}

	else {

		appendNode(&((**oLinkedList).next), outputLine);

	}

}

/*
 * The function which identify number of substrings in the infile strings and their ability of being Palindrome word
 * by calling two individual functions,
 * then stores returned results in output array pointer by calling an appendNode function
 */
void checkSubstringPalindrome2(char subStr[], char *iStringData[], Node **oLinkedList, int nrIOfileLines) {

	int row=0;

	int numSubStr;
	char *resultPaldr;

	char nextString[50];

	for (row = 0; row < nrIOfileLines; row++) {

		numSubStr = howManySubstrings(subStr, iStringData[row]);

		resultPaldr = getPalindrome(iStringData[row]);

		sprintf(nextString, "%s\t%i\t%s\n", iStringData[row], numSubStr, resultPaldr);

		appendNode(oLinkedList, nextString);

	}

}

//The function that reads two input file separately and stores their data into array of pointers
void readFile2(char filename[], char *ArrayPtr[]) {

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

		char *inLine = (char*) malloc(50 * sizeof(char));

		for (column = 0; column < 50; column++) {

			//Eliminate characters of new lines so that they will not affect subsequent output
			if (filestring[column] == '\n' || filestring[column] == '\r') {

				inLine[column] = '\0';

				break;

			}

			else {

				inLine[column] = filestring[column];

			}

		}

		ArrayPtr[row] = inLine;

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
	 * and returns result which is stored as row numbers of an input pointer array
	 */
	int ifNumLines = countFileLines(infile);
	char *iStringData[ifNumLines];

	/*
	 * This codes do the same as above, but here it reads the input file called subStrings.txt,
	 * and saves result as row of substring pointer array
	 */
	int subfNumLines = countFileLines(subfile);
	char *subArr[subfNumLines];

	int row = 0;

	//Calling a function that reads the data from the iStrings.txt (infile) and saves everything in pointer array
	readFile2(infile, iStringData);

	//Calling a function that reads the data from the subStrings.txt (subfile) and saves everything in pointer array
	readFile2(subfile, subArr);

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

		//firstNode will be the head of oLinkedList
		Node *firstNode = (Node*) malloc(sizeof(Node));

		(*firstNode).next = NULL;

		*(firstNode ->strData) = '\0';

		Node **oLinkedList = &firstNode;

		checkSubstringPalindrome2(subArr[row], iStringData, oLinkedList, ifNumLines);

		//Calling a function that writes the insides of the output pointer array into output file
		writeFile2(outfile, subArr[row], oLinkedList);

		//Printing contents of oLinkedlist
		printLinkedlist(*oLinkedList);

		//Clearing allocated memory in oLinkedList
		freeLinkedlist(*oLinkedList);

		row++;

	}

	//Clearing allocated memory in iStringData
	for (row = 0; row < ifNumLines; row++) {

		free(iStringData[row]);

	}

	//Clearing allocated memory in subArr
	for (row = 0; row < subfNumLines; row++) {

		free(subArr[row]);

	}

	return 0;
}

