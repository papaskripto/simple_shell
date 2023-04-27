#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 2048

void exit_shell(char *input);
void print_enviroment(char *args[64]);
size_t my_strcspn(const char *s, const char *reject);
char **find_path(char *command, char **envp);
int fork_process(char *command, char **args, char **envp);

int main(void)
{
    char user_input[MAX_COMMAND_LENGTH];
    char *argmnts[] = { NULL };
    char *env_vars[] = { NULL };
    int child_process_status;

    /* Check if standard input is a terminal*/
    if (isatty(STDIN_FILENO))
    {
        while (1)
        {
            /* display prompt and wait for user to input command */
            printf("DGShell: 😊 : ");
            fflush(stdout);

            if (fgets(user_input, MAX_COMMAND_LENGTH, stdin) == NULL)
            {
                /* handle the end of file condition */
                printf("\n");
                return 0;
            }

            /* remove newline character from input */
            user_input[my_strcspn(user_input, "\n")] = '\0';

            /* check & execute if exit command is input */
            exit_shell(user_input);

            /* call print_env if user input is "env" */
            argmnts[0] = user_input;
            argmnts[1] = NULL;
            print_enviroment(argmnts);

            /* execute command inputted by user */
            if (user_input != NULL && user_input[0] != '\0')
            {
                path = find_path(user_input, env_vars);
                child_process_status = fork_process(user_input, argmnts, path);
                free(path);
            }
        }
    }
    else {
        /* Standard input is not a terminal, read commands from standard input*/
        while (fgets(user_input, MAX_COMMAND_LENGTH, stdin) != NULL) {
            /* remove newline character from input */
            user_input[my_strcspn(user_input, "\n")] = '\0';

            /* check & execute if exit command is input */
            exit_shell(user_input);

            /* call print_env if user input is "env" */
            argmnts[0] = user_input;
            argmnts[1] = NULL;
            print_enviroment(argmnts);

            /* execute command inputted by user */
            if (user_input != NULL && user_input[0] != '\0')
            {
                path = find_path(user_input, env_vars);
                child_process_status = child_process(user_input, argmnts, path);
                free(path);
            }
        }
    }
    return 0;

}

