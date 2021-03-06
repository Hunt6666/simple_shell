#include "holberton_shell.h"

/**
 *stat_exec- checks if command exists and executes it if it does
 *@argv: the array of commands
 *@line: the line argv was made from (only to free)
 *@i: number of lines in shell
 *@env: environment
 *Return: 0 if success, -1 if need to break
 */
int stat_exec(char **argv, char *line, size_t i, char **env)
{
	struct stat st;
	int j;
	char *path = "_";
	char *envi = _getenv(path, env);
	(void)line;

	if (stat(argv[0], &st) != 0)
	{
		write(STDERR_FILENO, envi, _strlen(envi) + 1);
		write(STDERR_FILENO, ": ", 2);
		print_number(i);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, argv[0], strlen(argv[0]) + 1);
		write(STDERR_FILENO, ": not found\n", 12);
	}
	else
	{         /*execute command*/
		if (execve(argv[0], argv, NULL) == -1 && isatty(0))
		{
			write(STDERR_FILENO, envi, _strlen(envi) + 1);
			write(STDERR_FILENO, ": ", 2);
			print_number(i);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, argv[0], strlen(argv[0]) + 1);
			write(STDERR_FILENO, ": not found\n", 12);
		}
	}
	for (j = 0 ; argv[j] != NULL ; j++)
		free(argv[j]);
	free(argv);
	return (0);
}


/**
 *builtin- checks if the user input a built-in command and executes it
 *@env: the current environment
 *@argv: the list of arguments provided
 *@line: the line from getline
 *@extstat: status for empty exit
 *Return: 1 if builtin 0 if not
 */

int builtin(char **env, char **argv, char *line, int extstat)
{
	int i;

	if (_strcmp("env", argv[0]) == 0)/*envronment*/
	{
		if (argv[1] == NULL)
		{
			for (i = 0 ; env[i] ; i++)
			{
				write(1, env[i], _strlen(env[i]));
				write(1, "\n", 1);
			}
			free_shell(argv, line);
		}
		else
		{
			write(STDERR_FILENO, "env: ", 5);
			write(STDERR_FILENO, argv[1], strlen(argv[0]) + 1);
			write(STDERR_FILENO, ": No such file or directory\n",
			      28);
		}
		return (1);
	}
	else if (_strcmp("exit", argv[0]) == 0)/*exit*/
	{
		if (argv[1] == NULL)
		{
			free_shell(argv, line);
			exit(extstat);
		}
		i = atoi(argv[1]);
		free_shell(argv, line);
		exit(i);
	}
	return (0);
}
