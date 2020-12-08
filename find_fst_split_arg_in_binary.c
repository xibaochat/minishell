#include "minishell.h"

static char	**get_bin_path_arr(t_mini *sh)
{
	char	*path;
	char	**bin_path;

	path = ft_find_env(ENV_PATH, sh->env);
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

char	*cmd_is_inside_current_dir(char *cmd)
{
	char	*tmp;
	char	*current_place;
	char	*full_path;

	tmp = NULL;
	current_place = getcwd(NULL, 0);
	if (cmd_is_in_bin_dir(current_place, cmd))
	{
		tmp = ft_strjoin(current_place, "/");
		full_path = ft_strjoin(tmp, cmd);
		free_str(tmp);
		free_str(current_place);
		return (full_path);
	}
	else
		free_str(current_place);
	return (NULL);
}

char	*find_full_binary_path(char *cmd, t_mini *sh)
{
	char	**bin_path;
	char	*full_path;

	bin_path = NULL;
	full_path = cmd_is_inside_current_dir(cmd);
	if (full_path)
		return (full_path);
	if (is_binary_path(cmd)) //ex: /bin/ls, cmd is ls, bin_path is /bin/
		return (manage_binary_cmd(cmd, sh));
	else
		bin_path = get_bin_path_arr(sh);
	full_path = check_cmd_and_return_full_bin_path(cmd, bin_path);
	if (!full_path)
	{
		show_error_message(cmd, CMD_NO_FD, sh);
		ft_tabfree(bin_path);
		return (NULL);
	}
	return (full_path);
}
