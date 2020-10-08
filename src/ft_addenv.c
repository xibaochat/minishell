#include "minishell.h"

void ft_envadd(char **envp, char *expt, t_mini *sh)
{
    int i;
    char    **env;

    i = 0;
    while (envp[i])
        i++;
    if (expt != NULL)
        i++;
    if (!(env = malloc(sizeof(char *) * (i + 1))))
	{
		ft_putstr_fd("Fail Malloc\n", 2);
		exit(-1);
	}
    i = -1;
    while (envp[++i])
        env[i] = ft_strdup(envp[i]);
    if (expt != NULL)
	{
		expt = rm_quote_in_str(expt);
		env[i++] = ft_strdup(expt);
	}
    env[i] = NULL;
	/* if (sh->env) */
	/* 	ft_tabfree(sh->env); */
	sh->env = env;

/* ToDo: Check if basic env var exist, and create them if needed */
}
