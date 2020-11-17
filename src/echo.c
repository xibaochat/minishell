#include "minishell.h"

/*
** The "-n" option skips the '\n' after executing echo
*/

int	has_n_option(char *s)
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
	int	i;

	i = has_n_option(args[1]);
	while (args[++i])
	{
		if (args[i] && args[i][0])
		{
			ft_putstr(args[i]);
			if (args[i + 1] && args[i + 1][0])
				ft_putstr(" ");
		}
		// don't show str if it is empty echo "" v1 v2
	}
	if (!has_n_option(args[1]))
		ft_putstr("\n");
}
