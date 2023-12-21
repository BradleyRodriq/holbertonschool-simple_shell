#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "main.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void executeCommand(char *command);
void handleCtrlC(int signum);
void open_prompt(void);

/**
 * main - takes user input
 * Return: 0
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;

	signal(SIGINT, handleCtrlC);

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			open_prompt();

			if (getline(&input, &input_size, stdin) == -1)
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
		while (getline(&input, &input_size, stdin) != -1)
		{
			input[strcspn(input, "\n")] = '\0';

			if (strcmp(input, "exit") == 0)
			{
				break;
			}
			executeCommand(input);
		}
	}
	free(input);
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
	char **env = environ;
	char *dir;
	char *path_copy;
	char *path;
	char *token;
	char *args[MAX_ARGUMENTS];
	int i;

	pid = fork();

	if (pid == -1)
	{
		perror("Error forking");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		i = 0;
		token = strtok(command, " ");

		while (token != NULL && i < MAX_ARGUMENTS - 1)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}

		args[i] = NULL;

		if (args[0][0] == '/')
		{
			execve(args[0], args, environ);
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}

		path = NULL;
		for (; *env != NULL; env++)
		{
			if (strncmp(*env, "PATH=", 5) == 0)
			{
				path = *env + 5;
				break;
			}
		}

		if (path == NULL)
		{
			perror("Error with PATH");
			exit(EXIT_FAILURE);
		}

		path_copy = strdup(path);
		dir = strtok(path_copy, ":");

		while (dir != NULL)
		{
			char executable[MAX_COMMAND_LENGTH];

			snprintf(executable, sizeof(executable), "%s/%s", dir, args[0]);
			execve(executable, args, environ);
			dir = strtok(NULL, ":");
		}
		perror("Error executing command");
		free(path_copy);
		exit(EXIT_FAILURE);
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

/**
 * handleCtrlC - handle Ctrl+C signal
 * @signum: signal number
 */
void handleCtrlC(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n", 1);
	open_prompt();
}

/**
 * open_prompt - function that opens prompt
 * Return: returns nothing
 */

void open_prompt(void)
{
	printf("OzoneLayer$: ");
	fflush(stdout);
}
