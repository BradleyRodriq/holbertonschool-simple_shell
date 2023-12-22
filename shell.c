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

void CMDexe(char *command);
void runExecve(char *command, char *args[]);
void handleSIGINT(int signum);
void open_prompt(void);

/**
 * main - takes user input
 * Return: 0
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;

	signal(SIGINT, handleSIGINT);

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
			CMDexe(input);
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
			CMDexe(input);
		}
	}
	free(input);
	return (0);
}

/**
 * CMDexe - executes desired command and calls execve function
 * @command: the desired command
 */
void CMDexe(char *command)
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

		runExecve(args[0], args);

		perror("Error executing command");
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
 * handleSIGINT - handle Ctrl+C signal
 * @signum: signal number
 */
void handleSIGINT(int signum)
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

/**
 * runExecve - handles execve to run commands from bin
 * @command: the command to be handled
 * @args: the arguments to be handled
 */
void runExecve(char *command, char *args[])
{
	(void) command;

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
	else if (strcmp(args[0], "mv") == 0)
	{
		execve("/bin/mv", args, environ);
	}
	else if (strcmp(args[0], "cp") == 0)
	{
		execve("/bin/cp", args, environ);
	}
	else if (strcmp(args[0], "printf") == 0)
	{
		execve("/bin/printf", args, environ);
	}
	else if (strcmp(args[0], "echo") == 0)
	{
		execve("/bin/echo", args, environ);
	}
	else if (strcmp(args[0], "cat") == 0)
	{
		execve("/bin/cat", args, environ);
	}
	else if (strcmp(args[0], "vim") == 0)
	{
		execve("/bin/vim", args, environ);
	}
	else if (strcmp(args[0], "less") == 0)
	{
		execve("/bin/less", args, environ);
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
