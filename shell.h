#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stddef.h>

extern char **environ;
/* for  buffers */ 

#define MAX_ARGS 64 /* Maximum number of arguments for a command*/
#define MAX_PATHS 10 /* Maximum number of paths in the PATH environment */

/*for functions */
void exit_shell(char *input);
int my_strcmp(const char *str1, const char *str2);
void print_env(char *args[64]);
size_t my_strcspn(const char *s, const char *reject);
void fork_process(char *token, char *input, char *args[64]);
int find_path(char *args[64]);





#endif
