#include "shell.h"

#define MAX_COMMAND_LENGTH 2048
void exit_shell(char *input);
/*void print_enviroment(char *args[64]);*/
size_t my_strcspn(const char *s, const char *reject);
/*int find_path(char *args[64]);*/
/*void fork_process(char *token, char *input, char *args[64]);*/

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
		 /*       	print_enviroment(argmnts);*/
                switch (fork())
                {
                        case -1:
                                perror("fork");
                                exit(1);
                        case 0:
                        /* execute command inputted by user */
                        if (user_input != NULL && user_input[0] != '\0')
                        {
                                argmnts[0] = user_input;
                                if (execve(user_input, argmnts, env_vars) == -1)
                                {
                                        printf("Command not found: %s\n", user_input);
                                        exit(1);
                                }
                          } 

                          else
                          {
                           	/* handle an empty user input(command) */
                            	exit(0);
                           }
                           	break;
                            	default:
                                /* wait for child process to finish executing user input(command) */
                                wait(&child_process_status);
                                break;
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
            	/*print_enviroment(argmnts);*/

            	if (user_input != NULL && user_input[0] != '\0')
           	{
            		switch (fork())
			{
                		case -1:
                    		perror("fork");
                    		exit(1);
                	case 0:
                   	/* execute command inputted by user */
                   	/* if (user_input != NULL && user_input[0] != '\0')
		{
                        argmnts[0] = user_input;*/
                        if (execve(user_input, argmnts, env_vars) == -1)
		{
                         printf("Command not found: %s\n", user_input);
                         exit(1);
                 }
             
            
                        else
			{
                        	/* handle an empty user input(command) */
                        	exit(0);
                  	}
                    	break;
                default:
                    	/* wait for child process to finish executing user input(command) */
                    	wait(&child_process_status);
                    	break;
            	}
            }
        }
    }
    return 0;

}
