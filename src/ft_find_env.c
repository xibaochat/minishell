#include "minishell.h"

char	*ft_find_env(char *elem, char **env)
{
	int i;
	int j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] == elem[j])
			j++;
		if (j >= 1 && env[i][--j] == '=' && elem[j] == '=')
			return (env[i] + j + 1);
	}
	return (NULL);
}
