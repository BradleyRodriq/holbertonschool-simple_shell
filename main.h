#ifndef MAIN_H
#define MAIN_H

extern char **environ;

void executeCommand(char *command);
void handleCtrlC(int signum);
void open_prompt(void);

#endif
