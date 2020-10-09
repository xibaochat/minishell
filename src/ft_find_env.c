#include "minishell.h"

char	*ft_find_env(char *name, char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)))
			if (env[i][ft_strlen(name)] == '=')
				return (ft_strchr(env[i], '=') + 1);
	}
	return ("");
}
