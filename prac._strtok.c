#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "holberton_shell.h"

char **tok(char *st, char *dil)
{
	int i;
	char *str = malloc(sizeof(st));
	int spaces = 1;
	char *token;
	char **tokens;

	strcpy(str, st);
	for (i = 0 ; str[i] ; i++)
   	{
		if (str[i] == ' ')
		{
			spaces++;
		}
	}
	printf("counting spaces worked\n");
	tokens = malloc(sizeof(char*) * spaces);
	printf("malloc worked\n");
	token = _strtok(str, dil);
	for (i = 0 ; token != NULL ; i++)
	{
		tokens[i] = malloc(sizeof(token));
		tokens[i] = strcpy(tokens[i], token);
		token = _strtok(NULL, dil);
	}
	printf("strtok worked\n");
	/*for (i = 1 ; token[i] ; i++)
	  token[i] = strtok(NULL, dil);*/
	free(token);
	free(str);
	return (tokens);
}


int main()
{
	char *str = "Hello World";
	int i;
	char *dil = " ";
	char **token = tok(str, dil);

	for (i = 0 ; token[i] ; i++)
	{
		printf("%s\n", token[i]);
	}
	for (i = 0 ; token[i] ; i++)
		free(token[i]);
	free(token[i]);
	free(token);
	free(dil);
	free(str);
	return (0);
}
