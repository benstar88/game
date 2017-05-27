#include "randNum.h"
#include <stdio.h>


int main()
{
	seedRandom();

	int numberOfCounters = 6;
	
	int counters[numberOfCounters];

	for(int i = 0; i < numberOfCounters; ++i)
        {
		counters[i] = 0;
        }

	int numberOfTests = 20000;
	
	for(int i = 0; i < numberOfTests; i++)
	{
		int number = randNum(1, numberOfCounters);

		counters[number - 1]++;
	}
	
	int totalTests = 0;
	
	for(int i = 0; i < numberOfCounters; ++i)
	{
		printf("number of %ds = %d\n", i + 1, counters[i]); 
		totalTests += counters[i];
	}

	printf("sum of all tests = %d\n", totalTests);
	printf("expected number of tests = %d\n", numberOfTests);
	
	return 0;
}
