#include "minishell.h"

void	env(t_mini *sh)
{
	int	i;

	i = -1;
	if (sh->env)
	{
		while ((sh->env)[++i])
		{
			if (sh->has_env_i
				&& !ft_strcmp((sh->env)[i], BASIC_ENV_PATH))
				i++;
			else if ((sh->env)[i][0])
			{
				ft_putstr((sh->env)[i]);
				ft_putstr("\n");
			}
		}
		sh->last_return = 0;
	}
}
