#include "minishell.h"

char	*ft_find_env(char *elem, char **env)
{
	int i;
	int j;
	int lens;

	i = -1;
	while (env[++i])
	{
		j = 0;
		lens = ft_strlen(elem);
		if (!ft_strncmp(env[i], elem, lens))
		{
			if (elem[lens - 1] == '=')
				return (env[i] + lens);
			if (env[i][lens] == '=')
				return (env[i] + lens + 1);
		}
		/* while (env[i][j] == elem[j]) */
		/* 	j++; */
		/* if (j >= 1 && env[i][--j] == '=' && elem[j] == '=') */
		/* 	return (env[i] + j + 1); */
	}
	return (NULL);
}
