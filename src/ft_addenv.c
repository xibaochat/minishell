#include "minishell.h"

int	get_nb_env_var(t_mini *sh)
{
	int	i;

	i = 0;
	if (sh->env)
	{
		while (sh->env[i])
			i++;
	}
	return (i);
}

void	ft_envadd_2(char *expt, t_mini *sh, char **env)
{
	int		i;

	i = 0;
	if (sh->env)
	{
		while (sh->env[i])
		{
			env[i] = ft_strdup(sh->env[i]);
			++i;
		}
	}
	if (expt)
		env[i++] = ft_strdup(expt);
	if (sh->env)
		ft_tabfree(sh->env);
	sh->env = env;
	sh->last_return = 0;
}

void	ft_envadd(char *expt, t_mini *sh)
{
	int		nb;
	char	**env;
	int		i;

	nb = get_nb_env_var(sh);
	i = -1;
	env = (char **)malloc(sizeof(char *) * (nb + 2));
	if (!env)
	{
		ft_putstr_fd("Fail Malloc\n", 2);
		exit(-1);
	}
	while (++i < nb + 2)
		env[i] = NULL;
	ft_envadd_2(expt, sh, env);
}

void	cpy_env(t_mini *sh, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	sh->env = (char **)malloc(sizeof(char *) * (i + 1));
	while (j < i + 1)
		sh->env[j++] = NULL;
	j = -1;
	while (++j < i)
		sh->env[j] = ft_strdup(env[j]);
}
