#include "minishell.h"

void	env(t_mini *sh)
{
    int i;

    i = -1;
	if (sh->env)
	{
		while ((sh->env)[++i])
		{
			ft_putstr((sh->env)[i]);
			ft_putstr("\n");
		}
	}
}