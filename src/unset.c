#include "minishell.h"

/**
 * Replace given var in sh->env by an empty string
 */

void unset(char **arr, t_mini *sh)
{
	int i;
	int j;
	int lens;
	char *tmp;

	i = 1;  // Skip 'unset'
	while (arr[i])
	{
		j = 0;
		lens = ft_strlen(arr[i]);
		while (sh->env[j])
		{
			if (!ft_strncmp(arr[i], sh->env[j], lens)
				&& sh->env[j][lens] && sh->env[j][lens] == '=')
			{
				tmp = sh->env[j];
				sh->env[j] = ft_strnew(1);
				free(tmp);
			}
			j++;
		}
		i++;
	}
}
