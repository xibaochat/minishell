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

void    change_dir_for_other_opts(t_mini *sh, char *path, char *old_p)
{
	char *curr_path;

	//go to given path
    if (chdir(path) == -1)
	{
		cd_error_message(path);
		sh->last_return = 1;
		free_str(old_p);
	}
    else
    {
		curr_path = getcwd(NULL, 0);
		change_env_var_value(sh->env, old_p, ENV_OLDPWD);
        change_env_var_value(sh->env, curr_path, ENV_PWD);
		sh->last_return = 0;
    }
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
		free_str(new_v);
	}
}
