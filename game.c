#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "gameCommon.h"

/*************************************************/

/***************declare functions*****************/

int main();
int readLevelFile(char* fileName, place* outLevel);

/*************************************************/

/****************define program*******************/

int main()
{
	int fBPos = 0;
	char input[100];
	place level[max_level_size];

	int levelSize = readLevelFile("level.bin", level);

	//exit should be true if the level is empty, in other words, if levelSize is zero
	bool exit = levelSize == 0;

	while(!exit)
	{
		printf("\n\nWhat would you like to do?\nq = quit\nf = move forward\nb = move backward\nd = display game state\n: ");
		scanf("%s", input);

		if(strcmp(input, "q") == 0)
		{
			exit = true;
		}
		else if(strcmp(input, "f") == 0)
		{
			fBPos++;
			if(fBPos >= levelSize)
			{
				printf("Out of bounds. You can't go any further forward\n");
				fBPos--;
			}
		}
		else if(strcmp(input, "b") == 0)
		{
			fBPos--;
			if(fBPos < 0)
			{
				printf("Out of bounds. You can't go any further backward\n");
				fBPos++;
			}
		}
		else if(strcmp(input, "d") == 0)
		{
			if(level[fBPos] == desert)
			{
				printf("You are in the desert");
			}
			else if(level[fBPos] == woods)
			{
				printf("You are in the woods");
			}
			else if(level[fBPos] == lake)
			{
				printf("You are by a lake");
			}
			else if(level[fBPos] == mountains)
			{
				printf("You are in the mountains");
			}
			else if(level[fBPos] == grasslands)
			{
				printf("You are in the grasslands");
			}
			else if(level[fBPos] == village)
			{
				printf("You are in a village");
			}
			else if(level[fBPos] == path)
			{
				printf("You are on a path");
			}
		}
		else
		{
			printf("\nThat's not a valid option\n");
		}
	}

	return 0;
}

int readLevelFile(char* fileName, place* outLevel)
{
	//open the file
	FILE* inputFile = fopen(fileName, "rb");

	if(inputFile == NULL)
	{
		printf("Cannot find file: %s\n", fileName);
		return 0;
	}

	//read the level size
	int levelSize = 0;
	fread(&levelSize, sizeof(levelSize), 1, inputFile);

	//read the level into outLevel
	for(int index = 0; index < levelSize; ++index)
	{
		fread(&outLevel[index], sizeof(outLevel[index]), 1, inputFile);
	}

	//close the file
	fclose(inputFile);

	//return the level size
	return levelSize;
}

/*************************************************/
