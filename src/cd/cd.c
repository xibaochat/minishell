#include "minishell.h"

void cd_error_message(char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putendl_fd(ft_strjoin(": ", str), 2);
}

char	*get_extracted_path(char **av, char *env_var)
{
	char *path;
	int	i;

	i = 0;
	path = NULL;
	while (av[i])
	{
		path = ft_strnstr(av[i], env_var, ft_strlen(av[i]));
		if (path)
			break ;
		i++;
	}
	if (!(av[i]))
		return (NULL);
	return (path + ft_strlen(env_var));
}

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

void init_env_var(t_mini *sh)
{
	char *path;
	char *new_path;
	char *arr[3] = {"OLDPWD=", "PWD=", NULL};
	int i;

	i = -1;
	path = getcwd(NULL, 0);
	while (arr[++i])
	{
		//if did not find OLDPWD, or PWD in env, then set them
		if (get_matched_var_in_env(sh->env, arr[i]) == -1)
		{
			new_path = ft_strnew(ft_strlen(arr[i]) + ft_strlen(path) + 1);
			ft_strcat(new_path, arr[i]);
			ft_strcat(new_path, path);
			ft_envadd(new_path, sh);
		}
	}
}

int cd_to_current_dir_opt(char **arr)
{
	return (arr[1] &&
			!ft_strcmp(arr[1], "."));
}

void    change_dir_for_other_opts(t_mini *sh, char *path, char *old_p)
{
	char *curr_path;

	//go to given path
    if (chdir(path) == -1)
	{
		cd_error_message(path);
		sh->last_return = 1;
	}
    else
    {
		curr_path = getcwd(NULL, 0);
        change_env_var_value(sh->env, old_p, "OLDPWD=");
        change_env_var_value(sh->env, curr_path, "PWD=");
		sh->last_return = 0;
    }
}

void cd_to_current_dir(t_mini *sh)
{
	char *path;

	path = getcwd(NULL, 0);
	change_dir(sh, path);
}

void cd_to_home(t_mini *sh)
{
	char    *path;
	char	*curr_p;

	path = NULL;
	if (!(path = get_extracted_path(sh->env, "HOME=")))
	{
		ft_putstr_fd("[-] Home env variable is not define\n", 2);
		sh->last_return = 1;
	}
	else
	{
		change_dir(sh, path);
		sh->last_return = 0;
	}
}

void cd(char **arr, t_mini *sh)
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
		cd_to_current_dir(sh);
	//cd ~ or cd (to HOME)
	else if (ft_tablen(arr) == 1 || !ft_strcmp(arr[1], "~"))
		cd_to_home(sh);
	else
	{
		curr_p = getcwd(NULL, 0);
		change_dir_for_other_opts(sh, arr[1], curr_p);
	}
}
