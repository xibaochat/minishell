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

void	unset_var_recpy_env(char *name, t_mini *sh)
{
	int nb;
	int j;
	int i;
	char **tmp;

	nb = ft_tablen(sh->env);
	j = 0;
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * nb);
	while (j < nb)
		tmp[j++] = NULL;
	j = 0;
	while (sh->env[j])
	{
		if (!ft_strncmp(name, sh->env[j], ft_strlen(name))
			&& ((int)ft_strlen(name) == len_var_name(sh->env[j])))
			j++;
		else
			tmp[i++] = ft_strdup(sh->env[j++]);
	}
	ft_tabfree(sh->env);
	sh->env = tmp;
}

void	unset(char **arr, t_mini *sh)
{
	int		i;

	i = 0;
	while (arr[++i])
	{
		if (unset_var_is_valid(sh, arr[i]))
		{
			if (!is_new_var(arr[i], sh->env))
				unset_var_recpy_env(arr[i], sh);
		}
		else
			show_key_error_message(UNSET, arr[i]);
	}
	if (has_invalid_var(sh, arr))
		sh->last_return = 1;
	else
		sh->last_return = 0;
}
