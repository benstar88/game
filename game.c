#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "gameCommon.h"
#include "utilities/randNum.h"

/*************************************************/

/***************declare functions*****************/

int main();
int readLevelFile(char* fileName, place* outLevel);
void clearScreen();
void draw();
void randomEncounter();

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

		fseek(stdin,0,SEEK_END);
		
		printf("Welcome %s", name);
	}

	while(!exit)
	{
		printf(" \n \nWhat would you like to do? \nq = quit \nf = move forward \nb = move backward \nm = show map \n: ");
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
				randomEncounter(level[fBPos]);
			}
		}
		else if(strcmp(input, "b") == 0)
		{
			fBPos--;
			
			if(fBPos == ( 0 - 1))
			{
				printf("Out of bounds. You can't go any further backward");
				fBPos++;
			}
			else
			{
				printf("You have moved backward");
				randomEncounter(level[fBPos]);
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
			printf("That's not a valid option");
		}
		if(!exit)
		{
                	draw(level[fBPos]);
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

void draw(place position)
{
	printf("\n");
	if(position == desert)
	{
		printf("You are in the desert");
	}
	else if(position == woods)
	{
		printf("You are in the woods");
	}
	else if(position == lake)
	{
		printf("You are by a lake");
	}
	else if(position == mountains)
	{
		printf("You are in the mountains");
	}
	else if(position == grasslands)
	{
		printf("You are in the grasslands");
	}
	else if(position == village)
	{
		printf("You are in a village");
	}
	else if(position == path)
	{
		printf("You are on a path");
	}
}

void randomEncounter(place position)
{
	if(position == desert)
        {
		int random = randNum(0, 3);
		if(random == 1)
		{
			printf("\nyou met a camel");
		}
	}
	else if(position == woods)
        {
		int random = randNum(0, 5);
		if(random == 1)
                {
                        printf("\nyou met a deer");
                }
		else if(random == 2)
		{
			printf("\nyou met a bear");
		}
	}
	else if(position == lake)
        {
		int random = randNum(0, 2);
                if(random == 1)
                {
                        printf("\nyou met a duck");
                }
	}
	else if(position == mountains)
        {
		int random = randNum(0, 99);
                if(random == 1)
                {
                        printf("\nyou met a yeti");
                }
	}
	else if(position == grasslands)
        {
                int random = randNum(0, 5);
                if(random == 1)
                {
                        printf("\nyou met a bunny");
                }
        }
	else if(position == village)
        {
                int random = randNum(0, 2);
                if(random == 1)
                {
                        printf("\nyou met a villager");
                }
        }
	else if(position == path)
        {
                int random = randNum(0, 2);
                if(random == 1)
                {
                        printf("\nyou met a villager");
                }
        }
}
/*************************************************/
