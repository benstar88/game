#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "gameCommon.h"

/*************************************************/

/***************declare functions*****************/

int main();
int readLevelFile(char* fileName, place* outLevel);
void clearScreen();

/*************************************************/

/****************define program*******************/

int main()
{
	int fBPos = 0;
	char input[100];
	place level[max_level_size];

	clearScreen();

	int levelSize = readLevelFile("level.bin", level);

	//exit should be true if the level is empty, in other words, if levelSize is zero
	bool exit = levelSize == 0;

	if(!exit)
	{
		char name[100];
		printf("what is your name?: ");
		scanf("%s", name);
		
		printf("Welcome %s", name);
	}

	while(!exit)
	{
		printf("\n\nWhat would you like to do?\nq = quit\nf = move forward\nb = move backward\nd = display game state\nm = show map\n: ");
		scanf("%s", input);

		clearScreen();

		if(strcmp(input, "q") == 0)
		{
			exit = true;
		}
		else if(strcmp(input, "f") == 0)
		{
			fBPos++;
			
			if(fBPos >= levelSize)
			{
				printf("Out of bounds. You can't go any further forward");
				fBPos--;
			}
			else
			{
				printf("You have moved forward");
			}
		}
		else if(strcmp(input, "b") == 0)
		{
			if(fBPos < 0)
			{
				printf("Out of bounds. You can't go any further backward");
				fBPos++;
			}
			else
			{
				printf("You have moved backward");
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
		else if(strcmp(input, "m") == 0)
		{
			for(int i = 0; i < levelSize; i++)
			{
				if(level[i] == desert)
				{
					printf("desert  ");
				}
				else if(level[i] == woods)
				{
					printf("woods  ");
				}
				else if(level[i] == lake)
				{
					printf("lake  ");
				}
				else if(level[i] == mountains)
				{
					printf("mountains  ");
				}
				else if(level[i] == grasslands)
				{
					printf("grasslands  ");
				}
				else if(level[i] == village)
				{
					printf("village  ");
				}
				else if(level[i] == path)
				{
					printf("path  ");
				}
			}
		}
		else
		{
			printf("\nThat's not a valid option");
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

void clearScreen()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

/*************************************************/
