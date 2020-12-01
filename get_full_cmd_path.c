#include "minishell.h"

char	*get_full_cmd_path(char *cmd, t_mini *sh)
{
	char	*full_cmd_path;

	full_cmd_path = NULL;
	if (is_binary_path(cmd)
		&& ft_get_directory("minishell", cmd))
	{
		sh->last_return = 126;
		return (NULL);
	}
	full_cmd_path = find_full_binary_path(cmd, sh);
	return (full_cmd_path);
}
