#include "shell.h"

#define MAX_COMMAND_LENGTH 2048
void exit_shell(char *input);
void print_enviroment(char *args[64]);
int my_strcmp(const char *str1, const char *str2);
/*size_t my_strcspn(const char *s, const char *reject);*/
size_t my_strcspn(const char *s, const char *reject);
void fork_process(char *token, char *input, char *args[64]);
int find_path(char *args[64]);
char *my_strchr(const char *s, int c);

/**
 * main - function will display take user input and execute in custom shell
 * @isatty(STDIN_FILENO):checks if stdin is a terminal
 * Return: 0 on success
 */
int main(void)
{
	char user_input[MAX_COMMAND_LENGTH];
	char *argmnts[64] = { NULL };


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
			return (0);
		}
		/* remove newline character from input */
		user_input[my_strcspn(user_input, "\n")] = '\0';

		/* check & execute if exit command is input */
		exit_shell(user_input);
		/* call print_env if user input is "env" */
		argmnts[0] = user_input;
		argmnts[1] = NULL;
		print_enviroment(argmnts);

		/* tokenize input and fork a child process to execute each token */
		if (user_input != NULL && user_input[0] != '\0')
            {
                fork_process(user_input, user_input, argmnts);
            }
        }
    }
		else
		{
		/* Standard input is not a terminal, read commands from standard input*/
		while (fgets(user_input, MAX_COMMAND_LENGTH, stdin) != NULL)
		{

		/* remove newline character from input */
		user_input[my_strcspn(user_input, "\n")] = '\0';
		/* check & execute if exit command is input */
		exit_shell(user_input);

		/* call print_env if user input is "env" */
		argmnts[0] = user_input;
		argmnts[1] = NULL;
		print_enviroment(argmnts);

		if (user_input != NULL && user_input[0] != '\0')
		{
		/* tokenize input and fork a child process to execute each token */ 
                     fork_process(user_input, user_input, argmnts);
     
            }
        }
    }
	return (0);

}


