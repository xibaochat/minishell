#include "minishell.h"

/*cherche ENV VAR exists or not, and return its index in the ENV*/

int	get_matched_var_in_env(char **env, char *var)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
				return (i);
	}
	return (-1);
}
/*if dest direcory is not reacheablem show err message
** else change OLDPWD and PWD in the ENV, then free malloc var value
*/
void    go_to_required_directory(t_mini *sh, char *dest, char *src)
{
	char *pwd;

    if (chdir(dest) == -1)
	{
		cd_error_message(dest);
		sh->last_return = 1;
	}
    else
    {
		pwd = getcwd(NULL, 0);
		change_env_var_value(sh->env, src, ENV_OLDPWD);
        change_env_var_value(sh->env, pwd, ENV_PWD);
		sh->last_return = 0;
		free_str(pwd);
    }
	free_str(src);
	free_str(dest);
}
/*find the index in ENV and change VAR VALUE by new value*/
void change_env_var_value(char **env, char *new_v, char *varname)
{
    int i;
    char *tmp;
    char *s;
//    char *old_path;

//	old_path = NULL;
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
