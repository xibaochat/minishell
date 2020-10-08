#include "minishell.h"

int	get_matched_var_in_env(char **env, char *var)
{
	int i;
	char *old_p;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (i);
	}
	return (-1);
}

void change_env_var_value(char **env, char *new_v, char *varname)
{
    int i;
    char *old_path;
    char *tmp;
    char *s;

	old_path = NULL;
	tmp = NULL;
	i = get_matched_var_in_env(env, varname);
	if (i != -1)
	{
		tmp = env[i];
		s = ft_strnew(ft_strlen(varname) + ft_strlen(new_v) + 1);
		ft_strncat(s, varname, ft_strlen(varname));
		ft_strncat(s, new_v, ft_strlen(new_v));
		env[i] = s;
		free_str(tmp);
	}
}
