#pragma once

#define MAX_MONKEY_MATRIX_SIZE 2250

typedef struct {
    char name[5];
    char dec[12];
    long val;
} Monkey;

extern Monkey MonkeyMatrix[MAX_MONKEY_MATRIX_SIZE];
extern int MonkeyMatrixSize;

void FindMatrixSize()
{
	for (int i = 0; i < MAX_MONKEY_MATRIX_SIZE; i++)
	{
		if (MonkeyMatrix[i].name[0] == '\0')
		{
            MonkeyMatrixSize = i - 1;
            return;
		}
	}
}

void PrintMonkeyMatrix()
{
	for (int i = 0; i < MonkeyMatrixSize; i++)
	{
		printf("{ name = %s dec = %s val = %ld }\n", 
				MonkeyMatrix[i].name, 
				MonkeyMatrix[i].dec, 
				MonkeyMatrix[i].val);
	}
	printf("MonkeyMatrixSize = %d\n", MonkeyMatrixSize);
}

int FindMonkey(char *target)
{
	for (int i = 0; i < MonkeyMatrixSize; i++)
		if (strstr(MonkeyMatrix[i].name, target) != NULL)
			return i;
	return -1;
}
