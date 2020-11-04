#include "minishell.h"

/*find variable name is inside ENV or not
 and return its value
*/
char	*ft_find_env(char *elem, char **env)
{
	int i;
	int j;
	int lens;

	i = -1;
	while (env[++i])
	{
		j = 0;
		lens = ft_strlen(elem);
		if (!ft_strncmp(env[i], elem, lens))
		{
			if (elem[lens - 1] == '=')
				return (env[i] + lens);
			//to avoid elem is part of varname $PW
			if (env[i][lens] == '=')
				return (env[i] + lens + 1);
		}
	}
	return (NULL);
}
