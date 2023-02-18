#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "monkey.h"
#include "strutils.h" 

Monkey MonkeyMatrix[MAX_MONKEY_MATRIX_SIZE];
int MonkeyMatrixSize;

long ParseDeclaration(char dec[12])
{
	char name1[5] = { 0 };
	char name2[5] = { 0 };

	char op = dec[5];
	strcpy(name1, strsplit(dec, 0, 4));
	strcpy(name2, strsplit(dec, 7, 4));
	
	printf("dec = \"%s\"\n", dec);
	printf("name1 = \"%s\" op = \"%c\" name2 = \"%s\"\n",
			name1, op, name2);
	long name1_val = MonkeyMatrix[FindMonkey(name1)].val;
	long name2_val = MonkeyMatrix[FindMonkey(name2)].val;
	if (!name1_val || !name2_val)
		return 0;
	long result;

	switch(op)
	{
		case '+':
			result = name1_val + name2_val;
			break;
		case '-':
			result = name1_val - name2_val;
			break;
		case '/':
			result = name1_val / name2_val;
			break;
		case '*':
			result = name1_val * name2_val;
			break;
		default:
			printf("\"%c\" is an invalid op code!", op);
			exit(2);
	}

	printf("name1_val = %ld name2_val = %ld\nresult = %ld\n",
			name1_val, name2_val, result);
	return result;
}

void ParseInput()
{
	const char* INPUT_FILE = "input";
	FILE* fptr;
	char ch;

	fptr = fopen(INPUT_FILE, "r");
	
	if (NULL == fptr) 
	{
		printf("Error opening \"%s\"! Does the file exist?\n", INPUT_FILE);
		exit(1);
	}

	int mode, monkey_index, i;
	mode = monkey_index = i = 0;
	do
	{
		ch = fgetc(fptr);

		// Parse for name
		if (!mode)
		{
			if (ch == ':')
			{
				MonkeyMatrix[monkey_index].name[i] = '\0';
				mode++;
				i = 0;
				ch = fgetc(fptr); // skip the following space char
			}
			else
			{
				MonkeyMatrix[monkey_index].name[i] = ch;
				i++;
			}
		}
		// Parse for declaration
		else
		{
			if (ch == '\n')
			{
				MonkeyMatrix[monkey_index].dec[i] = '\0';
				monkey_index++;
				mode--;
				i = 0;
			}
			else
			{
				MonkeyMatrix[monkey_index].dec[i] = ch;
				i++;
			}
		}
	} while (ch != EOF);

	fclose(fptr);

	FindMatrixSize();

	// Set val to the constants provided
	for (int i = 0; i < MonkeyMatrixSize; i++)
		if (isdigit(MonkeyMatrix[i].dec[0]))
			MonkeyMatrix[i].val = atol(MonkeyMatrix[i].dec);

	int rootIndex = FindMonkey("root");
	do
	{
		for (int i = 0; i < MonkeyMatrixSize; i++)
		{
			if (MonkeyMatrix[i].val == 0)
			{
				printf("--------\n%s\n", MonkeyMatrix[i].name);
				long result = ParseDeclaration(MonkeyMatrix[i].dec);
				if (result) MonkeyMatrix[i].val = result;
			}
		}
	} while (MonkeyMatrix[rootIndex].val == 0);

	printf("----\nroot = %ld\n----\n", MonkeyMatrix[rootIndex].val);
}

int main()
{
	ParseInput();
	//PrintMonkeyMatrix();
	return 0;
}
