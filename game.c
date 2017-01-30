#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "gameCommon.h"
#include "utilities/randNum.h"
#include "printColor.h"

/*************************************************/

/***************declare functions*****************/

int main();
int readLevelFile(char* fileName, place* outLevel);
void clearScreen();
void draw();
int randomEncounter(char* name, int playerHealth, place position);
int PSR();
int fight(char* name, int playerHealth, char* animal);

/*************************************************/

/****************define program*******************/

int main()
{
	int playerHealth = 20;
	int fBPos = 0;
	char input[100];
	place level[max_level_size];

	clearScreen();

	int levelSize = readLevelFile("level.bin", level);

	//exit should be true if the level is empty, in other words, if levelSize is zero
	bool exit = levelSize == 0;

	//give the player a name
	char name[100];

	if(!exit)
	{
		printf("what is your name?: ");
		scanf("%s", name);

		fseek(stdin,0,SEEK_END);
		
		printBlu("Welcome %s", name);
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
				if(playerHealth < 20)
				{
					playerHealth++;
				}
				playerHealth = randomEncounter(name, playerHealth, level[fBPos]);
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
				playerHealth = randomEncounter(name, playerHealth, level[fBPos]);
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

int randomEncounter(char* name, int playerHealth, place position)
{
	char* animal;
	
	if(position == desert)
        {
		int random = randNum(0, 3);
		if(random == 1)
		{
			animal = "camel";
			printGrn("\nyou met a %s", animal);
		}
	}
	else if(position == woods)
        {
		int random = randNum(0, 5);
		if(random == 1)
                {
			animal = "deer";
                        printGrn("\nyou met a %s", animal);
                }
		else if(random == 2)
		{
			animal = "bear";
			printRed("\nyou met a %s", animal);
			playerHealth = fight(name, playerHealth, animal);
		}
	}
	else if(position == lake)
        {
		int random = randNum(0, 2);
                if(random == 1)
                {
			animal = "duck";
                        printGrn("\nyou met a %s", animal);
                }
	}
	else if(position == mountains)
        {
		int random = randNum(0, 99);
                if(random == 1)
                {
			animal = "yeti";
                        printRed("\nyou met a %s", animal);
			playerHealth = fight(name, playerHealth, animal);
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
			printRed("\nyou met a %s", animal);
			playerHealth = fight(name, playerHealth, animal);
		}
        }
	else if(position == village)
        {
                int random = randNum(0, 2);
                if(random == 1)
                {
			animal = "villager";
                        printBlu("\nyou met a %s", animal);
         		PSR();
		}
        }
	else if(position == path)
        {
                int random = randNum(0, 2);
                if(random == 1)
                {
			animal = "villager";
                        printBlu("\nyou met a %s", animal);
			PSR();
                }
        }

	return playerHealth;
}

int PSR()
{
	enum SPR
	{
		paper,
		scissors,
		rock
	};
	
        int PLA;
        int OPP;
	
	int choice;
	printf("\ndo you want to play paper scissors rock \n0 = yes \n1 = no \n:");
	scanf("%d", &choice);

	clearScreen();
	
	if(choice == 0)
	{
        	while(0 == 0)
        	{
	
	                printf("paper, scissors, rock \n0 = paper \n1 = scissors \n2 = rock \n: ");
	                scanf("%d", &PLA);
	
	                fseek(stdin,0,SEEK_END);
			clearScreen();

	                OPP = randNum(0, 2);
	
	                if(PLA == 0 && OPP == 1)
	                {
	                        printRed("scissors\n");
		                        printRed("you lost\n");
		                return 0;
	                }
	                else if(PLA == 1 && OPP == 2)
	                {
	                        printRed("rock\n");
	                        printRed("you lost\n");
	                        return 0;
	                }
	                else if(PLA == 2 && OPP == 0)
	                {
	                        printRed("paper\n");
	                        printRed("you lost\n");
	                        return 0;
	                }
	                else if(PLA == 0 && OPP == 2)
	                {
	                        printRed("rock\n");
	                        printGrn("you won\n");
	                        return 1;
	                }
	                else if(PLA == 1 && OPP == 0)
	                {
	                        printRed("paper\n");
	                        printGrn("you won\n");
	                        return 1;
	                }
	                else if(PLA == 2 && OPP == 1)
	                {
	                        printRed("scissors\n");
	                        printGrn("you won\n");
	                        return 1;
	                }
	                else
	                {
	                        printRed("%s\n", PLA);
				printBlu("tie\n");
        	        }
		}
	}
	else
	{
		return 2;
	}

        return 0;
}

int fight(char* name, int playerHealth, char* animal)
{
        int animalHealth = randNum(15, 20);
        int animalAttack;

        int doWhat;

        while(0 == 0)
        {
                printf("\n%s's health: %d \n%s's health: %d", name, playerHealth, animal, animalHealth);

                printf("\nwhat will you do (0 = attack, 1 = flee): ");
                scanf("%d", &doWhat);

		fseek(stdin,0,SEEK_END);
		clearScreen();

                if(doWhat == 1)
                {
			printBlu("you ran away");
                	return playerHealth;
                }
                else if(doWhat == 0)
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
                                break;
                        }

                        animalAttack = randNum(0, 2);
                        if(animalAttack == 0 || animalAttack == 1)
                        {
                                printf("%s used scratch", animal);
                                if(randNum(0, 4) == 1)
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
                                printf("%s used bite", animal);
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
                                return 20;
                        }
                }
        }
	return playerHealth;
}

/*************************************************/
