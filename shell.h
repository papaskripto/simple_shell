#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>

extern char **environ;

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} env_t;

/* main.c */
int cmd_exec(char **input, char *s, int *i, env_t **head);

/* get_path_env.c */
char **get_env_path(char *name, char **env);
char *find_path(char **s, char **env);
char *get_env(char *name, char **env);

/* my_strtok.c */
int token_count(char *str, char delim);
char **token_strtok(char *str, char delim);

/* print_prompt.c */
void print_prompt(void);
int my_putchar(char c);
void my_puts(char *str);

/* errors.c */
void print_error(int *i, char *s, char **argv);
void print_env_error(char **argv);
void print_exit_error(int *i, char *s, char **argv);
void print_main_error(char **av);
void print_cd_error(int *i, char *s, char **argv);

/* my_custom_funcs.c */
int my_strcmp(char *s1, char *s2);
char *mystr_concat(char *s1, char *s2);
char *my_strstr(char *haystack, char *needle);
int my_strncmp(char *s1, char *s2, unsigned int n);
char *my_strdup(char *str);

/* my_custom_funcs2.c */
int my_strlen(char *s);
char *my_strcpy(char *dest, char *src);

/* helper_functions.c */
void free_ptr(char **args);
void handle_sigint(int sig);
char **prs_lne(char *line, int get);

/* built_ins.c */
int check_builtin_cmd(char *line, char **argv, char *progg_nme,
		int *i, env_t **head);
long int handle_exit(char **tokens);
int handle_env(char **arv, env_t **head);
int handle_cd(char **arv, env_t **head);
void handle_pwd(char *path, char **env, env_t **head);

/* convert_functions.c */
char *convert_num_str(int num, int base);
long int atoi_(char *s);

/* 1__function.c */
env_t *add_node_at_end(env_t **head, char *str);
int node_at_index(env_t **head, char *str, int index);
int delete_index_node(env_t **head, unsigned int index);
int index_list_fnd(env_t *head, char *name);

/* 1_functs_two.c */
size_t list_length(const env_t *h);
size_t prt_lst(env_t *h);
void fr_lst(env_t **head);
int arr_2_lst(env_t **head, char **env);
char **lst_2_arr(env_t *head);

/* setenv_unsetenv.c */
int my_unsetenv(env_t **head, char **argv);
int my_setenv(env_t **head, char **argv, int args);
void handle_setenv(char **argv, env_t **head, int *i, char *prog_name);
void print_setenv_error(int *i, char *s, char **argv);

#endif
