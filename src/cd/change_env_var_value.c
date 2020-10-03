#include "minishell.h"

void change_env_var_value(char **env, char *new_v, char *varname)
{
    int i;
    char *old_path;
    char *tmp;
    char *s;

    i = -1;
	old_path = NULL;
	tmp = NULL;
    while (env[++i])
    {
       old_path = ft_strnstr(env[i], varname, ft_strlen(varname));
	   if (old_path)
            break ;
    }
    tmp = env[i];
    s = ft_strnew(ft_strlen(varname) + ft_strlen(new_v) + 1);
	 ft_strncat(s, varname, ft_strlen(varname));
    ft_strncat(s, new_v, ft_strlen(new_v));
    env[i] = s;
    free(tmp);
}
