#include "minishell.h"

char	**ft_envadd(char **envp, char *expt)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1 + 1))))
        return (NULL);
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	if (expt != NULL)
        env[i++] = ft_strdup(expt);
	env[i] = NULL;
	return (env);
}
