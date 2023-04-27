#include "shell.h"

/**
 * @find_path - searches for the command in the directories listed in PATH
 * @path:gets the value of the PATH environment variable
 * @path_copy:a copy of the PATH variable
 * @dir:directory
 * @command_path:Array to store the full path of the command
 * @command_found:Flag to keep track of whether the command was found or not 	* return: 0
 */
int find_path(char *args[64])
{
	
	char *path = getenv("PATH");
	char *path_copy = strdup(path);

	/* Tokenize the PATH variable by colon to get each directory */
	char *dir = strtok(path_copy, ":");
	int command_found = 0;
	char command_path[512];

	/* Check if the command is in the current directory */
	if (access(args[0], X_OK) == 0)
	{
		command_found = 1;
		return (0);
	}

	/* Loop through each directory in PATH and check if the command is there */
	while (dir != NULL)
	{
		/* Create the full path to the command */
		snprintf(command_path, 512, "%s/%s", dir, args[0]);

		/* Check if the command is executable in this directory */
		if (access(command_path, X_OK) == 0)
		{
			/* Command was found, update the args array with the full path */
			command_found = 1;
			strcpy(args[0], command_path);
			break;
		}

		/* Move to the next directory in PATH */
		dir = strtok(NULL, ":");
	}

	/* Free the memory used by the path copy */
	free(path_copy);

	/* If the command was not found in any directory, print an error message */
	if (!command_found)
	{
		printf("%s: command not found\n", args[0]);
		return (-1);
	}

	return (0);
}


char *my_strchr(const char *s, int c)
{
    while (*s != '\0') {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }
    return NULL;
}


/**
 * fork_process - function  child process to execute the command
 * @env:Array to store environment variables.
 * @i:Counter for the arguments
 * return: void
 */
char *my_strchr(const char *s, int c);
void print_enviroment(char *args[64]);
void fork_process(char *token, char *input, char *args[64])
{
	/* Array to store environment variables (not used in this shell) */
	char *env[1] = {NULL};
	int i = 0, j;

	/* Tokenize the user input by space to get each argument */
	token = strtok(input, " ");

	while (token != NULL && i < 63)
	{
		/* Store the argument in the args array */
		args[i++] = token;

		/* Move to the next token */
		token = strtok(NULL, "\n");
	}

	/* Set the last element in the args array to NULL */
	*(args + i) = NULL;

	/* Print the environment variables*/
	print_enviroment(args);

	/* Exit the program if the input is "exit" */
	exit_shell(input);

	/* Check if the command is a path to an executable file */
	if (my_strchr(args[0], '/') != NULL)
	{
		/* If the file is executable, execute it */
		if (access(args[0], X_OK) == 0)
		{
			if (execve(args[0], args, env) == -1)
			{
				perror("Unable to execute.");
				exit(1);
			}
		}
		else
		{
			/* If the file is not executable, print an error message */
			printf("./dgshell: command not found\n");
			exit(1);
		}
	}
	else
	{
		/* Declare and initialize the variables for the find_path and execve functions */
                char *arg_list[64];
                char *env_list[1] = {NULL};

                /* Copy the args array to the arg_list array */
                for ( j = 0; j < i; j++)
                        arg_list[j] = args[j];

                /* Add the NULL terminator to the arg_list array */
                arg_list[i] = NULL;
		/* Handle the 'PATH' commands */
		if (find_path(arg_list) == -1)
		exit(1);
		/* Execute the executable file */
		if (execve(arg_list[0], arg_list, env_list) == -1)
		{
			perror("Unable to execute.");
			exit(1);
		}
	}
}

