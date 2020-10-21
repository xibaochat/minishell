#include "minishell.h"

/*
 ** ft_printf_space prints the specific whitespace char
 */

void	ft_print_space(char c)
{
	if (c == 'f')
		write(1, "\f", 1);
	if (c == 't')
		write(1, "\t", 1);
	if (c == 'n')
		write(1, "\n", 1);
	if (c == 'r')
		write(1, "\r", 1);
	if (c == 'v')
		write(1, "\v", 1);
	return ;
}

/*
 ** Looking for var (for ex : $USER) within env and print it ; otherwise do nothing
 */

void	ft_print_var(char **args, int i, int j, char **env)
{
	char	*var;
	int	k;

	k = j + 1;
	if (args[i][k] == '$')
		ft_putstr(ft_find_env("$$", env));
	else
	{
		while (!ft_strchr("$'\" ", args[i][k]) && args[i][k])
			k++;
		var = ft_substr(args[i], j + 1, k - j - 1);
		ft_putstr(ft_find_env(var, env));
		/*	k = -1;
			while (env[++k])
			{
			if (!ft_strncmp(var, env[k], ft_strlen(var)) && env[k][ft_strlen(var)] == '=')
			write(1, env[k] + ft_strlen(var) + 1, ft_strlen(env[k]) - ft_strlen(var) - 1);
			}*/
		free(var);
		var = NULL;
	}
	return ;
}

int has_n_option(char *s)
{
	if (s)
	{
		if (s[0] == '-' && s[1] == 'n' && ft_strlen(s) == 2)
			return (1);
	}
	return (0);
}

void	echo(char **args)
{
	int i;
	int	n_option;

	i = 0;
	n_option = has_n_option(args[1]);
	if (n_option)
		i = 1;
	while (args[++i])
    {
		ft_putstr(args[i]);
		if (args[i + 1])
			ft_putstr(" ");
	}
	if (!n_option)
		ft_putstr("\n");
}
