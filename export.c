#include "minishell.h"

int		len_var_name(char *var)
{
	int		i;

	i = 0;
	while (var[i] && var[i] != '=' && !(var[i] == '+' && var[i + 1] == '='))
		i++;
	return (i);
}

int	is_new_var(char *s, char **env)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '=' && s[i] != '+')
		i++;
	while (env[j] && (ft_strncmp(s, env[j], i)
					  || (len_var_name(env[j]) != len_var_name(s))))
		j++;
	if (!env[j])
		return (1);
	return (0);
}

void	add_new_var_in_env(char *s, t_mini *sh)
{
	int i;

	i = len_var_name(s);
	if (s[i] && s[i] == '+')
		ft_strlcpy(s + i, s + i + 1, ft_strlen(s + i + 1) + 1);
	ft_envadd(s, sh);
}

void concatenate_values(char *s, char **env, int j)
{
	int i;
	char *str;

	i = len_var_name(s);
	if (has_equal_sign(env[j]))
		str = ft_strjoin(env[j], s + i + 2);
	else
		str = ft_strjoin(env[j], s + i + 1);
	free_str(env[j]);
	env[j] = str;
}

void replace_var_value(char *s, char **env)
{
	int i;
	int j;

	j = 0;
	i = len_var_name(s);
	while (env[j] && ft_strncmp(env[j], s, i))
		j++;
	if (s[i] == '='
		&& ft_strcmp(s + i, env[j] + i))
	{
		free_str(env[j]);
		env[j] = ft_strdup(s);
	}
	else if (s[i] && s[i] == '+')
		concatenate_values(s, env, j);
}

int is_same_str(char *s1, char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (!ft_strcmp(s1, arr[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(char **arr, t_mini *sh)
{
	int	i;

	i = 0;
	if (ft_tablen(arr) == 1)
		print_sort_env(sh->env, sh);
	else if (arr[1] && arr[1][0] == '-')
	{
		show_error_message("export:no option allowed\n", NULL, sh);
		return ;
	}
	while (arr[++i])
	{
		if (!ft_strcmp(arr[i], "") && sh->has_sub)
			print_sort_env(sh->env, sh);
		else if (has_invalid_char_in_env_name(arr[i]))
		{
			show_key_error_message(EXPORT, arr[i]);
			sh->last_return = 1;
		}
		else if (is_same_str(arr[i], sh->env))
			continue;
		else if (is_new_var(arr[i], sh->env))
			add_new_var_in_env(arr[i], sh);
		else
			replace_var_value(arr[i], sh->env);
	}
}
