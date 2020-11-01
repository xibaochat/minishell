# include "minishell.h"

void show_err_message(char *cmd, t_mini *sh, char **arr)
{
	if (is_binary_path(cmd))
	{
		show_bin_error_message(cmd, sh);
		ft_tabfree(arr);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_w_new_line_fd(": command not found", 2);
		sh->last_return = 127;
	}
}
