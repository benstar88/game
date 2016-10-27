#include <stdio.h>
#include <string.h>

#include "gameCommon.h"

int main()
{

	FILE *outputFile = fopen("level.bin", "w");
	int level_size = 0;

	while(level_size == 0)
	{
		printf("how big do you want your level?: ");
		scanf("%d", &level_size);

		if(level_size <= 0 || level_size > max_level_size)
		{
			printf("Your level must be a number between 1 and %d\n", max_level_size);
			level_size = 0;
		}
	}
	fwrite(&level_size, sizeof(place), 1, outputFile);

	int level[level_size];

	for(int index = 0; index < level_size; ++index)
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

	printf("Your level looks like this:\n");

	for(int index = 0; index < level_size; ++index)
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
		
	fwrite(level, sizeof(place), level_size, outputFile);
	
	fclose(outputFile);
	
	return 0;
}

