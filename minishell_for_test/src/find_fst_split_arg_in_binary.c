#include "minishell.h"

static char	**get_bin_path_arr(t_mini *sh)
{
	char	*path;
	char	**bin_path;

	path = ft_find_env(ENV_PATH, sh->env);
	if (!path)
		path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	bin_path = ft_split(path, ':');
	return (bin_path);
}

int	is_binary_path(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '/')
			return (1);
	}
	return (0);
}

char	*find_full_binary_path(char *cmd, t_mini *sh)
{
	char	**bin_path;
	char	*full_path;

	bin_path = NULL;
	full_path = NULL;
	if (is_binary_path(cmd)) //ex: /bin/ls, cmd is ls, bin_path is /bin/
		return (manage_binary_cmd(cmd, sh));
	else
		bin_path = get_bin_path_arr(sh);
	// check ls is inside $PATH or not
	full_path = check_cmd_and_return_full_bin_path(cmd, bin_path);
	if (!full_path)
	{
		show_error_message(cmd, CMD_NO_FD, sh);
		ft_tabfree(bin_path);
		return (NULL);
	}
	return (full_path);
}
