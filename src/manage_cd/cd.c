#include "minishell.h"

void	cd_error_message(char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_w_new_line_fd(str, 2);
}

int	cd_to_current_dir_opt(char **arr)
{
	return (arr[1] && !ft_strcmp(arr[1], "."));
}

void	cd_to_home(t_mini *sh, char *curr_p)
{
	char	*path;
	char	*dest;

	path = NULL;
	path = ft_find_env(ENV_HOME, sh->env);
	if (!path)
	{
		ft_putstr_w_new_line_fd(CD_HOME_ERR, 2);
		sh->last_return = 1;
	}
	else
	{
		dest = ft_malloc_and_copy(path);
		go_to_required_directory(sh, dest, curr_p);
	}
}

static void	cd_to_required_place(char **arr, t_mini *sh)
{
	char	*curr_p;
	char	*valid_path;

	curr_p = ft_find_env(ENV_PWD, sh->env);
	if (is_go_home_opt(arr, sh))
		cd_to_home(sh, curr_p);
	else
	{
		valid_path = ft_malloc_and_copy(extract_target_path(arr));
		go_to_required_directory(sh, valid_path, curr_p);
	}
}

void	ft_cd(char **arr, t_mini *sh)
{
	char	*curr_p;

	init_env_var(sh);
	if (has_multi_valid_arg(arr) > 1)
	{
		ft_putstr_w_new_line(strerror(EINVAL));
		sh->last_return = 1;
	}
	else if (cd_to_current_dir_opt(arr))
	{
		curr_p = getcwd(NULL, 0);
		change_env_var_value(sh->env, curr_p, ENV_OLDPWD);
		free_str(curr_p);
	}
	else
		cd_to_required_place(arr, sh);
}
