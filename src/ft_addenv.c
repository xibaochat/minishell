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
	if (s)
		i++;
	return (i);
}



void ft_envadd(char *expt, t_mini *sh)
{
    int i;
	int nb;
    char    **env;

	nb = get_nb_env_var(expt, sh);
	i = -1;
    if (!(env = malloc(sizeof(char *) * (nb + 1))))
	{
		ft_putstr_fd("Fail Malloc\n", 2);
		exit(-1);
	}
	while (++i < nb + 1)
		env[i] = NULL;
	i = -1;
	if (sh->env)
	{
		while (sh->env[++i])
			env[i] = ft_strdup(sh->env[i]);
	}
    if (expt)
	{
		expt = rm_quote_in_str(expt);
		env[++i] = ft_strdup(expt);
		free_str(expt);
	}
	if (sh->env)
		ft_tabfree(sh->env);
	sh->env = env;

/* ToDo: Check if basic env var exist, and create them if needed */
}
