#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* _strtok(char* str, const char* delimiters)
{
	static char* nextToken = NULL;

	if (str != NULL)
	{
		nextToken = str;
	} else if (nextToken == NULL)
	{
		return NULL;
	}

	nextToken += strspn(nextToken, delimiters);

	if (*nextToken == '\0')
	{
		return NULL;
	}

	char* token = nextToken;
	nextToken += strcspn(nextToken, delimiters);

	if (*nextToken != '\0')
	{
		*nextToken = '\0';
		nextToken++;
	} else {
		nextToken = NULL;
	}

	return token;
}

int main()
{
	const int maxInputLength = 1024;
	char input[maxInputLength];

	printf("> ");
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		perror("Error reading input");
		return 1;
	}

	const char delimiters[] = " \t\n";


	char* token = _strtok(input, delimiters);


	while (token != NULL)
	{
		printf("%s\n", token);
		token = _strtok(NULL, delimiters);
	}

	return 0;
}
