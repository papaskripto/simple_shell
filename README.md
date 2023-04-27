## 0x16. C - Simple Shell

This simple shell (DGShell 😊 : ) is a command line interpreter that replicates the sh program on UNIX. It is built to take in simple commands to navigate the terminal, work with files, and execute programs.

## How it works

0. Prints a prompt and waits for the user to input a command.

1. Creates a child process in which the command is checked.

2. Handles built-ins, aliases in the PATH, and local executable programs.

3. Then the child process is replaced by the command input, which accepts arguments.

4. After execution of the command input is done, the program returns to the parent process and prints the prompt

5. Now, the program is ready to receive a new command.

6. Ctrl+D and exit, exits the shell

7. Have been built to also work also in non interactive mode.

## How to compile & use

	gcc -Wall -Werror -Wextra -pedantic *.c -o dgshell
  
	./dgshell
  
## Authors 

	Doreen David
  
	Geofrey Ouma
