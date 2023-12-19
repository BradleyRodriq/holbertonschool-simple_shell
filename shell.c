#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
extern char **environ;

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

		if (strcmp(args[0], "ls") == 0)
		{
			execve("/usr/bin/ls", args, environ);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			execve("/usr/bin/env", args, environ);
		}
		else if (strcmp(args[0], "touch") == 0)
		{
			execve("/usr/bin/touch", args, environ);
		}
		else if (strcmp(args[0], "rm") == 0)
		{
			execve("/bin/rm", args, environ);
		}
		else if (strcmp(args[0], "pwd") == 0)
		{
			execve("/bin/pwd", args, environ);
		}
		else
		{
			execve(args[0], args, environ);
		}
		if (execve(args[0], args, environ) == -1)
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
