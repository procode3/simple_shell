#include "main.h"
char **get_args(char *str);
/**
 * main - takes in mutliple commands
 * @ac: args counter
 * @av: pointer to args
 * @env: environment vairable
 *
 * Return: zero on success, 1 on success
 */

int main(int ac, char **av, char *env[])
{
	char *buffer = NULL, **args, *str = NULL, *tok, *_return_cmd;
	size_t bufsize = 0;
	int i = 0, j = 0, len = 0;
	pid_t pid;
	(void)ac, (void)env;

	while (1)
	{
		printf("$ ");
		i = getline(&buffer, &bufsize, stdin);
		if (strcmp(buffer, "exit\n") == 0)
			break;
		if (i == -1)
		{
			printf("\n");
			break;
		}
		while (buffer[j] != '\0')
		{
			if (buffer[j] == ' ')
				len++;
			j++;
		}
		args =  malloc(sizeof(char *) * (len + 2));
		str = strndup(buffer, (i - 1));
		args = get_args(str);
		tok = strdup(args[0]);
		for (i = 0; args[i] != NULL; i++)
		_return_cmd = get_cmd(tok);
		if (_return_cmd == NULL)
		{
			perror(av[0]);
			continue;
		}
		args[0] = strdup(_return_cmd);
		i = 0;
		pid = fork();
		if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror("./shell");
				exit(-1);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	free(str);
	free(buffer);
	free(_return_cmd);
	return (0);
}

/**
 * get_args - creates an array from a string
 * @str: input command from getline
 *
 * Return: array of strings
 */

char **get_args(char *str)
{
	char **av, *token, *str_dup;
	int k = 0, len = 0;

	while (str[k] != '\0')
	{
		if (str[k] == ' ')
			len++;
		k++;
	}

	av = malloc(sizeof(char *) * (len + 2));
	str_dup = strdup(str);
	token = strtok(str_dup, " ");
	k = 0;
	while (token)
	{
		av[k] = strdup(token);
		token = strtok(NULL, " ");
		k++;
	}
	av[len + 1] = NULL;

	return (av);
}
