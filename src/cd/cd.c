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

void	change_dir(t_mini *sh, char *path, char *old_p)
{
	if (chdir(path) == -1)
		cd_error_message(path);
	else
	{
		change_env_var_value(sh->env, old_p, "OLDPWD=");
		change_env_var_value(sh->env, path, "PWD=");
	}
}

void init_env_var(t_mini *sh)
{
	char *path;
	char *new_path;
	char *arr[3] = {"OLDPWD=", "PWD=", NULL};
	int i;

	i = -1;
	path = getcwd(NULL, 0);
	while (++i < 2)
	{
		if (get_matched_var_in_env(sh->env, arr[i]) == -1)
		{
			new_path = ft_strnew(ft_strlen(arr[i]) + ft_strlen(path) + 1);
			ft_strcat(new_path, arr[i]);
			ft_strcat(new_path, path);
			ft_envadd(sh->env, new_path, sh);
		}
	}
}

void cd(char **arr, t_mini *sh)
{
	char *curr_p;

	init_env_var(sh);
	if (ft_tablen(arr) > 2)
        ft_putstr_w_new_line(strerror(EINVAL));
	else if (cd_to_home_opt(arr))
		cd_to_home(sh);
	else if (cd_to_current_dir_opt(arr))
		cd_to_current_dir(sh);
	else if (cd_to_pre_dir_opt(arr))
		cd_to_pre_dir(arr, sh);
	else
	{
		curr_p =  getcwd(NULL, 0);
		change_dir_for_other_opts(sh, arr[1], curr_p);
	}
}
