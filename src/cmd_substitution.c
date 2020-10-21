# include "minishell.h"

static int has_env_var(char *s, t_mini *sh)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '$')
			return (i);
	}
	return (-1);
}

char *var_value_is_in_env(char *s, t_mini *sh)
{
	int i;
	char *str;
	int lens;
	char *value;

	i = 0;
	if (s)
	{
		str = ft_strdup(s);
		value = ft_find_env(str, sh->env);
		if (value)
			return (value);
	}
	return (NULL);
}

void replace_var_by_value(char **s, int i, char *v, t_mini *sh)
{
	char *str;

	str = ft_strnew(i + ft_strlen(v) + 1);
	ft_strncat(str, *s, i);
	ft_strncat(str, v, ft_strlen(v));
	free_str(*s);
	*s = str;
}

void replace_var_sub_by_true_value(char **arr, t_mini *sh)
{
	int i;
	char *s;
	int index;
	char *v;

	i = 0;
	while (arr[++i])
	{
		// find $ signal, then get its index
		if ((index = has_env_var(arr[i], sh)) != -1)
		{
			if (v = var_value_is_in_env(arr[i] + index + 1, sh))
					replace_var_by_value(&arr[i], index, v, sh);
			else
			{
				free_str(arr[i]);
				arr[i] = ft_strnew(1);
			}
		}
	}
}
