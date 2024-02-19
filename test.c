// To test isPrime()

#include <stdio.h>
#include "prime.c"
#define USE_CASES_COUNT 11
#define MAX_CASE_LENGTH 10

void main()
{
	char UseCases[][ MAX_CASE_LENGTH ] = { "1234", "-12343", "55", "5", "", "qwdwq", "%^^@", "123(#&#", "@&*@&12334", "13", "1737" };
	int ExpectedValues[] = { 0, -1, 0, 1, -1, -1, -1, -1, -1, 1, 0};

	int Counter = 0;

	int UseCasesSucessCount = 0;

	while ( Counter < USE_CASES_COUNT)
	{
		if (ExpectedValues[Counter] == isPrime(UseCases[Counter]))
			UseCasesSucessCount++;
		else
			printf("UseCase %d is failed. Value: %s\n", Counter + 1, UseCases[Counter]);

		Counter++;
	}

	if (UseCasesSucessCount == USE_CASES_COUNT)
		printf("\nALL CASES ARE PASSED\n");
}