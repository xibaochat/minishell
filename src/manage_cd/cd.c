#include "minishell.h"

void cd_error_message(char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_w_new_line_fd(str, 2);
}

//go to the path user asked
void	change_dir(t_mini *sh, char *path)
{
	if (chdir(path) == -1)
	{
		cd_error_message(path);
		sh->last_return = 1;
	}
	else
		sh->last_return = 0;
}

int cd_to_current_dir_opt(char **arr)
{
	return (arr[1] &&
			!ft_strcmp(arr[1], "."));
}

void cd_to_home(t_mini *sh)
{
	char    *path;
	char	*curr_p;

	path = NULL;
	if (!(path = ft_find_env(ENV_HOME, sh->env)))
	{
		ft_putstr_w_new_line_fd(CD_HOME_ERR, 2);
		sh->last_return = 1;
	}
	else
	{
		change_dir(sh, path);
		sh->last_return = 0;
	}
}

void ft_cd(char **arr, t_mini *sh)
{
	char *curr_p;

	//if env no PWD, OLDPWD, set
	init_env_var(sh);
	if (ft_tablen(arr) > 2)
	{
		ft_putstr_w_new_line(strerror(EINVAL));
		sh->last_return = 1;
	}
	//manage: cd .
	else if (cd_to_current_dir_opt(arr))
		;
	//cd ~ or cd (to HOME)
	else if (ft_tablen(arr) == 1 || !ft_strcmp(arr[1], "~"))
		cd_to_home(sh);
	else
	{
		curr_p = getcwd(NULL, 0);
		change_dir_for_other_opts(sh, arr[1], curr_p);
	}
}
