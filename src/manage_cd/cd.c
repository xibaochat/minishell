#include "minishell.h"

void cd_error_message(char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_w_new_line_fd(str, 2);
}

//go to the path user asked
void	change_home_dir(t_mini *sh, char *path)
{
	char *curr_p;

	if (chdir(path) == -1)
	{
		cd_error_message(path);
		sh->last_return = 1;
	}
	else
	{
		curr_p = getcwd(NULL, 0);
		change_env_var_value(sh->env, curr_p, ENV_OLDPWD);
		sh->last_return = 0;
	}
}

int cd_to_current_dir_opt(char **arr)
{
	return (arr[1] &&
			!ft_strcmp(arr[1], "."));
}

/*
** Update PWD et OLDPWD env var, and change working
** directory based on HOME env var value
*/
void cd_to_home(t_mini *sh)
{
	char    *path;
	char	*curr_p;
	char	*home_path;

	path = NULL;
	home_path = NULL;
	if (!(path = ft_find_env(ENV_HOME, sh->env)))
	{
		ft_putstr_w_new_line_fd(CD_HOME_ERR, 2);
		sh->last_return = 1;
	}
	else
		change_home_dir(sh, path);
}

void ft_cd(char **arr, t_mini *sh)
{
	char *curr_p;
	char *valid_path;

	//if env no PWD, OLDPWD, set
	init_env_var(sh);

	//manage cas: cd $dewd $OLDPWD $PWD, has multiple destinations
	if (has_multi_valid_arg(arr) > 1)
	{
		ft_putstr_w_new_line(strerror(EINVAL));
		sh->last_return = 1;
	}
	//manage: cd .
	else if (cd_to_current_dir_opt(arr))
		;
	//situation cd $drewrfd $OLDPWD, if the varis "\0", the go home
	// unset OLDPWD PWD, then cd $PWD
	else if (is_go_home_opt(arr, sh))
		cd_to_home(sh);
	else
	{
		curr_p = getcwd(NULL, 0);
		valid_path = extract_target_path(arr);
		change_dir_for_other_opts(sh, valid_path, curr_p);
	}
}
