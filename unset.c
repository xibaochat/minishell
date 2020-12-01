#include "minishell.h"

static int	unset_var_is_valid(t_mini *sh, char *str)
{
	int	i;

	(void)sh;
	i = 0;
	if (ft_isdigit(str[0])
		|| has_equal_sign(str))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	has_invalid_var(t_mini *sh, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!unset_var_is_valid(sh, arr[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	remove_var_in_env(char *str, t_mini *sh)
{
	int		i;
	int		lens;
	char	*tmp;

	i = 0;
	lens = ft_strlen(str);
	while (sh->env[i])
	{
		if (!ft_strncmp(str, sh->env[i], lens)
			&& sh->env[i][lens] && sh->env[i][lens] == '=')
		{
			tmp = sh->env[i];
			sh->env[i] = ft_strnew(1);
			free_str(tmp);
		}
		i++;
	}
}

void	unset(char **arr, t_mini *sh)
{
	int		i;

	i = 0;
	while (arr[++i])
	{
		if (unset_var_is_valid(sh, arr[i]))
			remove_var_in_env(arr[i], sh);
		else
			show_key_error_message(UNSET, arr[i]);
	}
	if (has_invalid_var(sh, arr))
		sh->last_return = 1;
	else
		sh->last_return = 0;
}
