#include "minishell.h"

int get_nb_env_var(char *s, t_mini *sh)
{
	int i;

	i = 0;
	if (sh->env)
	{
		while (sh->env[i])
			i++;
	}
	return (i);
}

void ft_envadd(char *expt, t_mini *sh)
{
    int i;
	int nb;
    char    **env;

	nb = get_nb_env_var(expt, sh);
	i = -1;
    if (!(env = (char **)malloc(sizeof(char *) * (nb + 2))))
	{
		ft_putstr_fd("Fail Malloc\n", 2);
		exit(-1);
	}
	while (++i < nb + 2)
		env[i] = NULL;

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
	{
		expt = rm_quote_in_str(expt);
		env[i++] = ft_strdup(expt);
		free_str(expt);
	}
	if (sh->env)
		ft_tabfree(sh->env);
	sh->env = env;
}

void cpy_env(t_mini *sh, char **env)
{
	int i;
	int j;

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
