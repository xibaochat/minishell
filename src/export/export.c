#include "minishell.h"

void	ft_tabfree(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (tab)
	{
		while (tab[i])
			i++;
		while (j < i)
			free_str(tab[j]);
		free(tab);
		tab = NULL;
	}
}

//export maobe=kitten, if maobe=cat before, now need to change the value
int replace_var_value(char **env, char *s)
{
	int i;
	int j;
	char *tmp;
	char *s1;

	i = 0;
	j = -1;
	tmp = NULL;
	while (s[i] && s[i] != '=')
		i++;
	while (env[++j])
	{
		if (!ft_strncmp(env[j], s, i + 1))
		{
			s1 = rm_quote_in_str(s);
			tmp = env[j];
			env[j] = s1;
			free_str(tmp);
			return (1);
		}
	}
	return (0);
}

void add_new_var_in_env(char *str, t_mini *sh)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (str[i] && str[i] != '=')
		i++;
	while (sh->env[j])
	{
		if (ft_strncmp(sh->env[j], str, i + 1))
			j++;
		else
			return ;
	}
	ft_envadd(sh->env, str, sh);
}

void export_add_var(char *var_value, t_mini *sh)
{
	char *tmp;
	char *s;

	if (!replace_var_value(sh->env, var_value))
		add_new_var_in_env(var_value, sh);
}

void export(char **arr, t_mini *sh)
{
	if (ft_tablen(arr) > 2)
    {
        ft_putstr(strerror(WRONG_ARG));
        return ;
    }
	else if (ft_tablen(arr) == 1)
		display_env_w_prefix(arr,sh-> env);
	else if (invalid_export_var_val(arr[1]))
		return (show_export_error_message(arr[1]));
	else
		export_add_var(arr[1], sh);
}
