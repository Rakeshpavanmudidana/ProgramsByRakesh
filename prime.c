// isPrime 

#include <stdio.h>
#include <string.h>

int isPrime(char* numericValue)
{
	int counter = 0;

	int number = 0;

	int length = strlen(numericValue);

	// printf("%s",numericValue);

	if (length < 1)
		return -1;
	// printf("%s",numericValue);

	while ( counter < length )
	{
		if (isdigit(numericValue[counter]))
		{
			number = number * 10 + (numericValue[counter] - '0'); 
		}
		else
		{
			return -1;
		}

		counter++;

	}

	if ( !(number % 2) )
		return 0;

	int count = 3;

	while ( count * count <= number )
	{
		if (number % count == 0)
		{
			return 0;
		}

		count += 2;

	}

	return 1;

}
