/*
 ============================================================================
 Name        : sample_code.c
 Author      : Roderick Buenviaje
 Version     :
 Copyright   : RB2013
 Description : Sample code
 ============================================================================
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Macro and Defines */
#define TRUE 1
#define FALSE 0
#define OK 0
#define FAIL -1
#define MAX_LENGTH 256
#define OUTPUT_FILE "Output.txt"


/* Function Prototypes */
int palindromeCheck(char *pString);
int subsetPrint(unsigned int iNVal);

// Check whether or not entered string is a palindrome
int palindromeCheck(char *pString)
{
	int iStartPos = 0;
	int iEndPos = 0;
	char buff[MAX_LENGTH];

	if (pString == NULL)
	{
		// Debug statement should be added here if integrated into a larger program
		return FALSE;
	}

	memcpy(buff, pString, MAX_LENGTH);

	// remove \0 character from string and array starts at index 0
	iEndPos = strlen(pString) - 2;

	while (iStartPos <= iEndPos)
	{
		if ((buff[iStartPos] >= 0x41) &&
				(buff[iStartPos] <= 0x5A))
		{
			// Make case insensitive
			buff[iStartPos] += 0x20;
		}

		if ((buff[iEndPos] >= 0x41) &&
				(buff[iEndPos] <= 0x5A))
		{
			// Make case insensitive
			buff[iEndPos] += 0x20;
		}

		// Check value of char and increment/decrement
		if (buff[iStartPos++] != buff[iEndPos--])
		{
			return FALSE;
		}
	}

	return TRUE;
}

// Prints all subsets of N to file
int subsetPrint(unsigned int iNVal)
{
	FILE *fpSubset;
	fpSubset = fopen(OUTPUT_FILE, "w");

	int i = 0;
	int j = 0;

	fprintf(fpSubset, "{ }\n");

	int iMaskFilter = (1 << iNVal);
	for (i = 1; i < iMaskFilter; i++)
	{
		fprintf(fpSubset, "{ ");
		for (j = 0; j < iNVal; j++)
		{
			if ((i & (1 << j)) > 0) //The j-th element is used
			{
				fprintf(fpSubset, "%d ", j + 1);
			}
		}
		fprintf(fpSubset, "}\n");
	}

	fclose(fpSubset);
	return 0;
}

int main(void)
{
	char buff[MAX_LENGTH];
	int iInput = 0;
	int iReturnVal = 0;
	int exitFlag = 1;
	printf("This program will allow you to do some programming tests. Enter a number:\n");

	while (exitFlag)
	{
		printf("1 - Palindrome Check\n");
		printf("2 - Print all subsets of N\n");
		printf("3 - Exit\n\n");

		fgets(buff, 5, stdin);
		iInput = atoi(buff);
		switch (iInput)
		{
			case 1:
				printf("Enter string to check if it is a palindrome:\n");
				fgets(buff, MAX_LENGTH, stdin);
				iReturnVal = palindromeCheck(buff);
				if (iReturnVal)
				{
					printf("String is a palindrome\n\n");
				}
				else
				{
					printf("String is NOT a palindrome\n\n");
				}
				break;

			case 2:
				printf("Enter value from 1-30 to print all subsets:\n");
				printf("Warning: Values greater than 20 may take a LONG time\n");
				fgets(buff, MAX_LENGTH, stdin);
				iInput = atoi(buff);
				if ((iInput <= 0) ||
						(iInput > 127))
				{
					printf("Invalid input.\n\n");
				}
				else
				{
					if (subsetPrint(iInput) == 0)
					{
						printf("Subsets printed to %s:\n\n", OUTPUT_FILE);
					}
				}
				break;

			case 3:
				exitFlag = 0;
				break;

			default:
				break;
		}
	}
	return EXIT_SUCCESS;
}
