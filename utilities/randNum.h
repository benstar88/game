#include <stdlib.h>
#include <time.h>

void seedRandom()
{
	srand(time(NULL));
}

/*
* This function will return a random number between lowLimit and highLimit
* including lowLimit and including highLimit
* if a number cannot be selected, the function will return 0
*/
int randNum(lowLimit, highLimit)
{
	int modBy = (highLimit - lowLimit) + 1;
	
	if(modBy > RAND_MAX)
	{
		return 0;
	}

	if(lowLimit > highLimit)
	{
		return 0;
	}

	if(lowLimit == highLimit)
	{
		return lowLimit;
	}

	int randNumber = rand() % modBy;
	randNumber = randNumber + lowLimit;
	
	return randNumber;
}
