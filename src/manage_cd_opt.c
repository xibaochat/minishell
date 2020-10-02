#include "minishell.h"

void cd_to_home(t_mini *sh)
{
	char    *path;

	path = get_extracted_path(sh->env, "HOME=");
	change_dir(path);
}

void cd_to_current_dir(void)
{
	char *path;

	path = getcwd(NULL, 0);
	change_dir(path);
}

void cd_to_pre_dir(char **arr, t_mini *sh)
{
	char	*path;
	char	*home;
	int		lens;
	char	*s;

	path = get_extracted_path(sh->env, "OLDPWD=");
	home = get_extracted_path(sh->env, "HOME=");
	lens = ft_strlen(home);
	s = ft_strnew(ft_strlen(path) - lens + 1 + 1);
	s[0] = '~';
	ft_strncat(s, path + lens, ft_strlen(path) - lens);
	if (!ft_strcmp(arr[1], "-"))
		ft_putstr_w_new_line(s);
	change_dir(path);
}
