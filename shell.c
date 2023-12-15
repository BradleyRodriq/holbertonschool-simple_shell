#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void executeCommand(char *command);

/**
 * main - takes user input
 * Return: 0
 */
int main(void)
{
	char input[MAX_COMMAND_LENGTH];

	if (isatty(fileno(stdin)))
	{
		while (1)
		{
			printf("$: ");

			if (fgets(input, sizeof(input), stdin) == NULL)
			{
				break;
			}
			input[strcspn(input, "\n")] = '\0';

			if (strcmp(input, "exit") == 0)
			{

				break;
			}
			executeCommand(input);
		}
	}
	else
	{
		while (fgets(input, sizeof(input), stdin) != NULL)
		{
			input[strcspn(input, "\n")] = '\0';

			if (strcmp(input, "exit") == 0)
			{
				break;
			}
			executeCommand(input);
		}
	}
	return (0);
}

/**
 * executeCommand - executes desired command
 * @command: the desired command
 */
void executeCommand(char *command)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("Error forking");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[MAX_ARGUMENTS];
		int i = 0;
		char *token = strtok(command, " ");

		while (token != NULL && i < MAX_ARGUMENTS - 1)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}

		args[i] = NULL;
		if (execvp(args[0], args) == -1)
		{
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error waiting for child process");
			exit(EXIT_FAILURE);
		}
	}
}

