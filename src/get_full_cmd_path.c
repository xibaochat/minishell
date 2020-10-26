# include "minishell.h"

char	*get_full_cmd_path(char *cmd, t_mini *sh)
{
	char *full_cmd_path;

	full_cmd_path = NULL;
	if(ft_get_directory("minishell", cmd))
	{
		sh->last_return = 126;
		return (NULL);
	}
	full_cmd_path = find_full_binary_path(cmd, sh);
	if (!full_cmd_path)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_w_new_line_fd(": command not found", 2);
		sh->last_return = 127;
		return (NULL);
	}
	return (full_cmd_path);
}
