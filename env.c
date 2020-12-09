#include "minishell.h"

void	env(t_mini *sh, char **arr)
{
	int	i;

	i = -1;
	if (arr && ft_tablen(arr) > 1)
	{
		sh->last_return = 127;
		ft_printf("env : ‘%s’: No such file or directory\n", arr[1]);
	}
	else if  (sh->env)
	{
		while ((sh->env)[++i])
		{
			if (sh->has_env_i
				&& !ft_strcmp((sh->env)[i], BASIC_ENV_PATH))
				continue;
			else if ((sh->env)[i][0] && has_equal_sign(sh->env[i]))
			{
				ft_putstr((sh->env)[i]);
				ft_putstr("\n");
			}
		}
		sh->last_return = 0;
	}
}
