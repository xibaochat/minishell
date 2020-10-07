#include "minishell.h"

void cd_to_home(t_mini *sh)
{
	char    *path;
	char	*curr_p;

	path = NULL;
	if (!(path = get_extracted_path(sh->env, "HOME=")))
		ft_putstr_fd("[-] Home env variable is not define\n", 2);
	else
	{
		curr_p = getcwd(NULL, 0);
		change_dir(sh, path, curr_p);
	}
}

void cd_to_current_dir(t_mini *sh)
{
	char *path;
	char *old_p;

	path = getcwd(NULL, 0);
	old_p = get_extracted_path(sh->env, "OLDPWD=");
	change_dir(sh, path, old_p);
}

void cd_to_pre_dir(char **arr, t_mini *sh)
{
	char	*path;
	char	*home;
	int		lens;
	char	*s;
	char	*curr_p;

	path = get_extracted_path(sh->env, "OLDPWD=");
	home = get_extracted_path(sh->env, "HOME=");
	lens = ft_strlen(home);
	s = ft_strnew(ft_strlen(path) - lens + 1 + 1);
	s[0] = '~';
	ft_strncat(s, path + lens, ft_strlen(path) - lens);
	if (!ft_strcmp(arr[1], "-"))
		ft_putstr_w_new_line(s);
	//change_oldpwd(sh);
	curr_p = getcwd(NULL, 0);
	change_dir(sh, path, curr_p);
}
