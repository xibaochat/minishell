#include "minishell.h"

int with_n_option(char *s)
{
	if (s)
	{
		if (s[0] == '-' && s[1] == 'n' && ft_strlen(s) == 2)
			return (1);
	}
	return (0);
}

void	pipe_echo(char **args, int *pipe_fd)
{
	int i;
	int	n_option;

	i = 0;
	n_option = with_n_option(args[1]);
	if (n_option)
		i = 1;
	while (args[++i])
    {
		if (args[i] && args[i][0])
		{
			ft_putstr_fd(args[i], pipe_fd[WRITE_END]);
			if (args[i + 1] && args[i + 1][0])
				ft_putstr_fd(" ", pipe_fd[WRITE_END]);
		}
		// don't show str if it is empty echo "" v1 v2
	}
	if (!n_option)
		ft_putstr_fd("\n", pipe_fd[WRITE_END]);
}
