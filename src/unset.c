#include "minishell.h"

/**
 * Replace given var in sh->env by an empty string
 */

static int unset_var_is_valid(t_mini *sh, char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[0])
		|| has_equal_sign(str))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) &&
            str[i] != '_')
            return (0);
		i++;
	}
	return (1);
}

static int has_invalid_var(t_mini *sh, char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (!unset_var_is_valid(sh, arr[i]))
			return (1);
		i++;
	}
	return (0);
}

void unset(char **arr, t_mini *sh)
{
	int i;
	int j;
	int lens;
	char *tmp;

	i = 0;  // Skip 'unset'
	while (arr[++i])
	{
		//check unset var is valid or not ex: unset 1a2b(NOT valid)
		if (unset_var_is_valid(sh, arr[i]))
		{
			j = 0;
			lens = ft_strlen(arr[i]);
			while (sh->env[j])
			{
				//find which env var should be replaced by an empty str
				if (!ft_strncmp(arr[i], sh->env[j], lens)
					&& sh->env[j][lens] && sh->env[j][lens] == '=')
				{
					tmp = sh->env[j];
					sh->env[j] = ft_strnew(1);
					free_str(tmp);
				}
				j++;
			}
		}
		else
			show_key_error_message(UNSET, arr[i]);
	}
	if (has_invalid_var(sh, arr))
		sh->last_return = 1;
	else
		sh->last_return = 0;
}
