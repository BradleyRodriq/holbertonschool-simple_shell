#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	long max_pid = sysconf(_SC_CHILD_MAX);

	printf("Maximum PID: %ld\n", max_pid);

	return (0);
}
