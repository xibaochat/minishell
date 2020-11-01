# include "minishell.h"

void show_error_message(char *cmd, char *err, t_mini *sh)
{
	 ft_putstr_fd(cmd, 2);
	 ft_putstr_w_new_line_fd(err, 2);
	 sh->last_return = 127;
}
