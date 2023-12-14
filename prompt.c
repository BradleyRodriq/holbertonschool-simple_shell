#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	while (1)
	{
		printf("$ ");

		char input [100];

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			break;
		}
		printf("%s", input);
	}
	return (0);
}
