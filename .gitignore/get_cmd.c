#include "main.h"

/**
 * get_cmd - looks for valid paths/files
 * @name: commands from user
 *
 * Return: pointer to valid path or NULL
 */

char *get_cmd(const char *name)
{
	char *path, *tok, *cmd, **paths, *command;
	struct stat st;
	int i = 0, j = 0, len = 0;

	if (stat(name, &st) == 0)
	{
		cmd = strdup(name);
		return (cmd);
	}
	path = _getenv("PATH");
	while (path[j] != '\0')
	{
		if (path[j] == ':')
			len++;
		j++;
	}
	tok = strtok(path, ":");
	paths = malloc(sizeof(char *) * (len + 2));
	while (tok)
	{
		paths[i] = tok;
		tok = strtok(NULL, ":");
		i++;
	}
	i = 0;
	while (paths[i])
	{
		cmd = malloc(sizeof(char) * (strlen(paths[i]) + strlen(name) + 1));
		strcat(cmd, paths[i]), strcat(cmd, "/"), strcat(cmd, name);
		if (stat(cmd, &st) == 0)
		{
			command = strdup(cmd);
			free(paths);
			return (command);
		}
		i++;
	}
	free(path);
	free(cmd);
	return (NULL);
}
