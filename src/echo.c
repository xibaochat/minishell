#include "minishell.h"

/*
 ** ft_quoted checks if the whitespace symbol (for ex: \n) is surrounded by quote marks
 */

int	ft_quoted(char *s, int	j)
{
	if (s[j - 1] == '\'' && s[j + 2] == '\'')
		return (1);
	if (s[j - 1] == '\"' && s[j + 2] == '\"')
		return (1);
	return (0);
}

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


/*
 ** Checking quotes --> quote[0] : single quote opened / quote[1] : double quote
 ** note : ft_strrmv removes all char of 2nd param from 1st param and returns the new string
 */

void	echo(char **args, t_mini *sh)
{
	int	i;
	int	j;
	int	quote[2];

	if (ft_tablen(args) == 1)
		write(1, "\n", 1);
	i = 0;
	if (!ft_strcmp(ft_strrmv(args[1], SPACE), "-n"))
	{
		if (ft_tablen(args) <= 2)
		{
			ft_putendl(strerror(WRONG_ARG));
			return ;
		}
		else
			i = 1;
	}
	quote[0] = 0;
	quote[1] = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '\'' && quote[1])
				write(1, &args[i][j], 1);
			if (args[i][j] == '\"' && quote[0])
				write(1, &args[i][j], 1);
			if ((args[i][j] == '$' && quote[0]))
				write(1, &args[i][j], 1);
			if (!ft_strchr("\'\"$\\", args[i][j]))
				write(1, &args[i][j], 1);
			if (args[i][j] == '\'')
			{
				if (quote[0])
					quote[0] = 0;
				else if (!quote[1])
					quote[0] = 1;
			}
			if (args[i][j] == '\"')
			{
				if (quote[1])
					quote[1] = 0;
				else if (!quote[0])
					quote[1] = 1;
			}
			if (args[i][j] == '\\')
			{
				if (ft_strchr("ftnrv", args[i][j + 1]) && ft_quoted(args[i], j))
					ft_print_space(args[i][j + 1]);
				else if (args[i][j + 1] == '\\')
					write(1, "\\", 1);
				else if (args[i][j + 1] == '\0' || ft_strchr(SPACE, args[i][j + 1]))
					ft_putendl("Can't echo a single \'\\\'");
				else
					write(1, &args[i][j + 1], 1);
				j += 2;
			}
			if (args[i][j] == '$' && !quote[0])
			{
				ft_print_var(args, i, j, sh->env);
				j++;
				while (!ft_strchr("$'\" ", args[i][j]))
					j++;
				j--;
			}
		}
	}
	if (!ft_strcmp(ft_strrmv(args[1], SPACE), "-n"))
		return ;
	write(1, "\n", 1);
	return ;
}
