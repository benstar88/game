#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "gameCommon.h"
#include "utilities/randNum.h"

void automatic();
void manual();
int main();
int selectLevelSize();
bool shouldGenerateAutomatically();
void printLevel(int levelSize, place* level);

int main()
{
	int levelSize = selectLevelSize();

	if(shouldGenerateAutomatically())
	{
		automatic(levelSize);
	}
	else
	{
		manual(levelSize);
	}
	
	return 0;
}

void manual(int levelSize)
{
	FILE* outputFile = fopen("level.bin", "w");

	fwrite(&levelSize, sizeof(place), 1, outputFile);

	int level[levelSize];

	for(int index = 0; index < levelSize; ++index)
	{
		printf("Enter the type of place for position %d \n", index);
		printf("desert = 0 \nwoods = 1 \nlake = 2 \nmountains = 3 \ngrasslands = 4 \nvillage = 5 \npath = 6 \n: ");

		scanf("%d", &level[index]);

		if(level[index] < 0 || level[index] >= number_of_places)
		{
			printf("The type of place must be a number between 0 and %d\n", number_of_places - 1);
			--index;
		}
	}
	
	printLevel(levelSize, level);
		
	fwrite(level, sizeof(place), levelSize, outputFile);
	
	fclose(outputFile);
}

void automatic(int levelSize)
{
        FILE *outputFile = fopen("level.bin", "w");
	
	seedRandom();

        fwrite(&levelSize, sizeof(place), 1, outputFile);
	
        int level[levelSize];

        for(int index = 0; index < levelSize; ++index)
        {
                level[index] = randNum(0, 6);
        }

	printLevel(levelSize, level);

        fwrite(level, sizeof(place), levelSize, outputFile);

        fclose(outputFile);
}

int selectLevelSize()
{
	int levelSize = 0;
	while(levelSize == 0)
	{
		printf("how big do you want your level?: ");
		scanf("%d", &levelSize);

		if(levelSize <= 0 || levelSize > max_level_size)
		{
			printf("Your level must be a number between 1 and %d\n", max_level_size);
			levelSize = 0;
		}
		fseek(stdin,0,SEEK_END);
	}

        printf("level size = %d\n", levelSize);

	return levelSize;
}

bool shouldGenerateAutomatically()
{
	char autoOrManual[100];

	for(;;)
	{
		printf("Would you like to design your own level, or generate one automatically? \nm = manual \na = automatic \n:  ");
		scanf("%s", autoOrManual);
		
		// Clear the stdin buffer in case there were more characters waiting
		fseek(stdin,0,SEEK_END);
		
		if(strcmp(autoOrManual, "m") == 0)
		{
			return false;
		}
		else if(strcmp(autoOrManual, "a") == 0)
		{
			return true;
		}

		printf("\n");
	}
}

void printLevel(int levelSize, place* level)
{
	
	printf("Your level looks like this:\n");

        for(int index = 0; index < levelSize; ++index)
        {
                switch(level[index])
                {
                        case desert:
                                printf("desert\n");
                                break;
                        case woods:
                                printf("woods\n");
                                break;
                        case lake:
                                printf("lake\n");
                               break;
                        case mountains:
                                printf("mountains\n");
                                break;
                        case grasslands:
                                printf("grasslands\n");
                                break;
                        case village:
                                printf("village\n");
                                break;
                        case path:
                                printf("path\n");
                                break;
                        default:
                                printf("%d\n", level[index]);
                                break;
                }
        }
}
