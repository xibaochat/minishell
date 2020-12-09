#include "minishell.h"

//export maobe=kitten, if maobe=cat before, now need to change the value

int	replace_var_value(char **env, char *s)
{
	int		i;
	int		j;
	char	*new_v;

	i = 0;
	j = -1;
	while (s[i] && s[i] != '=')
		i++;
	while (env[++j])
	{
		if (!ft_strncmp(env[j], s, i + 1))
		{
			new_v = ft_malloc_and_copy(s);
			free_str(env[j]);
			env[j] = new_v;
			return (1);
		}
	}
	return (0);
}

void	add_new_var_in_env(char *str, t_mini *sh)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+')
		ft_strlcpy(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
	ft_envadd(str, sh);
}

/*check var is inside ENV or not, if not add var and its value in ENV*/

void	export_add_var(char *var_value, t_mini *sh)
{
	if (!replace_var_value(sh->env, var_value))
		add_new_var_in_env(var_value, sh);
}

void	ft_export(char **arr, t_mini *sh)
{
	int	i;

	i = 0;
	if (ft_tablen(arr) == 1)
		print_sort_env(sh->env, sh);
	while (arr[++i])
	{
		if (!ft_strcmp(arr[i], "") && sh->has_sub)
			print_sort_env(sh->env, sh);
		else if (has_invalid_char_in_env_name(arr[i]))
		{
			show_key_error_message(EXPORT, arr[i]);
			sh->last_return = 1;
		}
		else
			export_add_var(arr[i], sh);
	}
}
