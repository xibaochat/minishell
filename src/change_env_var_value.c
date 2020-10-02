#include "minishell.h"

void change_env_var_value(char **env, char *new_p, char *var)
{
    int i;
    char *old_path;
    char *tmp;
    char *s;

    i = -1;
    while (env[++i])
    {
       old_path = ft_strnstr(env[i], var, ft_strlen(env[i]))\
;
        if (old_path)
            break ;
    }
    tmp = env[i];
    s = ft_strnew(ft_strlen(var) + ft_strlen(new_p) + 1);
    ft_strncat(s, var, ft_strlen(var));
    ft_strncat(s, new_p, ft_strlen(new_p));
    env[i] = s;
    free(tmp);
}
