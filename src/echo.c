#include "minishell.h"

/*
** The "-n" option skips the '\n' after executing echo
*/

static int	str_is_all_n(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] == 'n')
		i++;
	if (!s[i])
		return (1);
	else
		return (0);
}

int	has_n_option(char *s)
{
	if (s)
	{
		if (s[0] == '-' && s[1] == 'n' && str_is_all_n(s))
			return (1);
	}
	return (0);
}

void	echo(char **args)
{
	int	i;
	int	mark;
	int	has_n;

	mark = 0;
	i = 0;
	while (args[++i])
	{
		while (has_n_option(args[i]) && !mark)
		{
			has_n = 1;
			i++;
		}
		if (args[i] && args[i][0])
		{
			ft_putstr_echo(args[i]);
			if (args[i + 1] && args[i + 1][0])
				ft_putstr(" ");
			mark = 1;
		}
	}
	if (has_n)
		ft_putstr("\n");
}
