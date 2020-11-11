#include "minishell.h"

void	pipe_env(int *fd, t_mini *sh)
{
    int i;

    i = -1;
	if (sh->env)
	{
		while ((sh->env)[++i])
		{
			if ((sh->env)[i][0])
			{
				ft_putstr_fd((sh->env)[i], fd[1]);
				ft_putstr_fd("\n", fd[1]);
			}
		}
		sh->last_return = 0;
	}
}
