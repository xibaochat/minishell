#include "minishell.h"

int	get_equal_index(char *s)
{
	int i;

	i = -1;
	if (s)
	{
		while (s[++i])
			if (s[i] == '=')
				return (i + 1);
	}
	return (i);
}

char	**get_sort_env(char **env)
{
	int	i;
	char *s;

	i = 0;
	while (env[i] && env[i + 1])
	{
		if (ft_strcmp(env[i], env[i + 1]) > 0)
		{
			s = env[i];
			env[i] = env[i + 1];
			env[i + 1] = s;
			i = -1;
		}
		i++;
	}
	return (env);
}

char *extract_name(char *s)
{
	int i;
	char *str;

	i = 0;
	i = get_equal_index(s);
	str = ft_strnew(i + 1);
	ft_strncat(str, s, i);
	return (str);
}

void	print_sort_env(char **env, t_mini *sh)
{
	int		i;
	char	**tmp;
	char	*name;

	i = 0;
	tmp = get_sort_env(env);
	while (tmp[i])
	{
		name = extract_name(tmp[i]);
		if ((sh->has_env_i && !ft_strcmp(name, "PATH="))
			|| !ft_strcmp(name, "_="))
			i++;
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(name, 1);
			ft_printf("\"%s\"\n", ft_find_env(name, tmp));
			i++;
		}
		free_str(name);
	}
}
