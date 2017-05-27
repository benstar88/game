#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "gameCommon.h"
#include "utilities/randNum.h"
#include "printColor.h"
/***************globals***************************/

int playerHealth = 20;
int wins = 0;
int loses = 0;
char name[50];

/***************declare functions*****************/

int main();
int readLevelFile(char* fileName, place* outLevel);
void clearScreen();
void draw();
void randomEncounter(char* name, place position);
void PSR();
void fight(char* animal);

/****************define program*******************/

int main()
{
	int playerHealth = 20;
	int fBPos = 0;
	char input[100];
	place level[max_level_size];

	seedRandom();
	clearScreen();

	int levelSize = readLevelFile("level.bin", level);

	//exit should be true if the level is empty, in other words, if levelSize is zero
	bool exit = levelSize == 0;

	if(!exit)
	{
		printf("what is your name? \n: ");
		scanf("%s", name);
		
		fseek(stdin,0,SEEK_END);
		
		printBlu("Welcome %s", name);
	}

	while(!exit)
	{
		printf(" \n \nWhat would you like to do? \nq = quit \nf = move forward \nb = move backward \nm = show map \ns = stats \n: ");
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
				if(playerHealth < 20)
				{
					playerHealth++;
				}
				randomEncounter(name, level[fBPos]);
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
				if(playerHealth < 20)
				{
					playerHealth++;
				}
				randomEncounter(name, level[fBPos]);
			}
		}
		else if(strcmp(input, "m") == 0)
		{
			for(int i = 0; i < levelSize; i++)
			{
				if(level[i] == desert)
				{
					if(i == fBPos)
					{
						printBlu("desert ");
					}
					else
					{
						printf("desert ");
					}
				}
				else if(level[i] == woods)
				{
					if(i == fBPos)
					{
						printBlu("woods ");
					}
					else
					{
						printf("woods ");
					}
				}
				else if(level[i] == lake)
				{
					if(i == fBPos)
					{
						printBlu("lake ");
					}
					else
					{
						printf("lake ");
					}
				}
				else if(level[i] == mountains)
				{
					if(i == fBPos)
					{
						printBlu("mountains ");
					}
					else
					{
						printf("mountains ");
					}
				}
				else if(level[i] == ocean)
				{
					if(i == fBPos)
					{
						printBlu("ocean ");
					}
					else
					{
						printf("ocean ");
					}
				}
				else if(level[i] == grasslands)
				{
					if(i == fBPos)
					{
						printBlu("grasslands ");
					}
					else
					{
						printf("grasslands ");
					}
				}
				else if(level[i] == village)
				{
					if(i == fBPos)
					{
						printBlu("village ");
					}
					else
					{
						printf("village ");
					}
				}
				else if(level[i] == path)
				{
					if(i == fBPos)
					{
						printBlu("path ");
					}
					else
					{
						printf("path ");
					}
				}

			}

		}
		else if(strcmp(input, "s") == 0)
		{
			printf("name: %s \nwins: %d \nloses: %d \nin bag: %s \nhealth: %d", name, wins, loses, "WIP", playerHealth);
		}
		else
		{
			printRed("That's not a valid option");
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
		printRed("Cannot find file: %s\n", fileName);
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
	else if(position == ocean)
	{
		printf("You are on the beach");
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

void randomEncounter(char* name, place position)
{
	char* animal;

	if(position == desert)
	{
		int random = randNum(0, 2);
		if(random == 0)
		{
			animal = "camel";
			printGrn("\nyou met a %s", animal);
		}
	}
	else if(position == woods)
	{
		int random = randNum(0, 2);
		if(random == 0)
		{
			animal = "deer";
			printGrn("\nyou saw a %s", animal);
		}
		else if(random == 2)
		{
			animal = "bear";
			printRed("\nyou disturbed a %s", animal);
			fight(animal);
		}
	}
	else if(position == lake)
	{
		int random = randNum(0, 1);
		if(random == 0)
		{
			animal = "duck";
			printGrn("\nyou met a %s", animal);
		}
	}
	else if(position == mountains)
	{
		int random = randNum(0, 9);
		if(random == 0)
		{
			animal = "yeti";
			printRed("\nyou met a %s", animal);
			fight(animal);
		}
	}
	else if(position == ocean)
	{
		int random = randNum(0, 3);
		if(random == 0)
		{
			animal = "turtle";
			printGrn("\nyou met a %s", animal);
		}
		else if(random == 3)
		{
			animal = "shark";
			printRed("\nyou found a %s", animal);
			fight(animal);
		}
	}
	else if(position == grasslands)
	{
		int random = randNum(0, 4);
		if(random == 0 || random == 1)
		{
			animal = "bunny";
			printGrn("\nyou met a %s", animal);
		}
		else if(random == 2 || random == 3)
		{
			animal = "killerBunny";
			printRed("\nyou upset a %s", animal);
			fight(animal);
		}
	}
	else if(position == village)
	{
		int random = randNum(0, 2);
		if(random == 0)
		{
			animal = "villager";
			printBlu("\nyou met a %s", animal);
			PSR();
		}
		else if(random == 2)
		{
			animal = "rat";
			printBlu("\nyou saw a %s", animal);
		}
	}
	else if(position == path)
	{
		int random = randNum(0, 2);
		if(random == 0)
		{
			animal = "villager";
			printBlu("\nyou met a %s", animal);
			PSR();
		}
	}
}

void PSR()
{
	enum
	{
		paper,
		scissors,
		rock
	};

	int opponent;
	char choice[2];
	
	printf("\ndo you want to play paper scissors rock \ny = yes \nn = no \n:");
	scanf("%s", choice);

	clearScreen();

	if(strcmp(choice, "y") == 0)
	{
		for(;;)
		{
			printf("paper, scissors, rock \np = paper \ns = scissors \nr = rock \n: ");
			scanf("%s", choice);
			fseek(stdin,0,SEEK_END);
			clearScreen();

			opponent = randNum(0, 2);

			if(strcmp(choice, "p") == 0 && opponent == scissors)
			{
				printRed("your opponent picked scissors\n");
				printRed("you lost\n");
				loses++;
				break;
			}
			else if(strcmp(choice, "s") == 0 && opponent == rock)
			{
				printRed("your opponent picked rock\n");
				printRed("you lost\n");
				loses++;
				break;
			}
			else if(strcmp(choice, "r") == 0 && opponent == paper)
			{
				printRed("your opponent picked paper\n");
				printRed("you lost\n");
				loses++;
				break;
			}
			else if(strcmp(choice, "p") == 0 && opponent == rock)
			{
				printRed("your opponent picked rock\n");
				printGrn("you won\n");
				wins++;
				break;
			}
			else if(strcmp(choice, "s") == 0 && opponent == paper)
			{
				printRed("your opponent picked paper\n");
				printGrn("you won\n");
				wins++;
				break;
			}
			else if(strcmp(choice, "r") == 0 && opponent == scissors)
			{
				printRed("your opponent picked scissors\n");
				printGrn("you won\n");
				wins++;
				break;
			}
			else
			{
				printBlu("tie\n");
			}
		}
	}
}

void fight(char* animal)
{
	int animalHealth = randNum(15, 20);
	int animalAttack;

	char choice[2];

	for(;;)
	{
		printf("\n%s's health: %d \n%s's health: %d", name, playerHealth, animal, animalHealth);

		printf("\na = attack \nf = flee \n: ");
		scanf("%s", choice);

		fseek(stdin,0,SEEK_END);
		clearScreen();

		if(strcmp(choice, "f") == 0)
		{
			printBlu("you ran away");
			break;
		}
		else if(strcmp(choice, "a") == 0)
		{
			printf("you attack\n");
			if(randNum(0, 3) == 1)
			{
				printBlu("you missed\n");
			}
			else
			{
				animalHealth = animalHealth - 4;
			}

			if(animalHealth <= 0)
			{
				printGrn("you won!!!\n");
				wins++;
				break;
			}

			animalAttack = randNum(0, 2);
			if(animalAttack == 0 || animalAttack == 1)
			{
				printf("the %s used nip", animal);
				if(randNum(0, 3) == 1)
				{
					printRed("\nthe %s missed", animal);
				}
				else
				{
					playerHealth = playerHealth - 3;
				}
			}
			else if(animalAttack == 2)
			{
				printf("the %s used bite", animal);
				if(randNum(0, 4) == 1)
				{
					printRed("\nthe %s missed", animal);
				}
				else
				{
					playerHealth = playerHealth - 5;
				}
			}
			if(playerHealth <= 0)
			{
				printRed("\nyou lost!!!\n");
				playerHealth = 20;
				loses++;
				break;
			}
		}
	}
}
