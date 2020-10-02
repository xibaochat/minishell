#include "minishell.h"

static void cd_error_message(char *str)
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
	return (path + ft_strlen(env_var));
}

void	change_dir(char *path)
{
	if (chdir(path) == -1)
		cd_error_message(path);
}

void cd(char **arr, t_mini *sh)
{
	if (ft_tablen(arr) > 2)
        ft_putstr_w_new_line(strerror(EINVAL));
	else if (cd_to_home_opt(arr))
		cd_to_home(sh);
	else if (cd_to_current_dir_opt(arr))
		cd_to_current_dir();
	else if (cd_to_pre_dir_opt(arr))
		cd_to_pre_dir(arr, sh);
	else
		change_dir(arr[1]);

}
