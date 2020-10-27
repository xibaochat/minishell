# include "minishell.h"


void ft_not_quit(int sig)
{
	char **buffer;

	buffer = get_buffer();
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	g_sh.last_return = 130;
	ft_putstr_w_new_line_fd("", 2);
	print_prompt(&g_sh);
}

void ft_signal(int i, t_mini *sh)
{
	if (i == 1)
	{
		signal(SIGINT, ft_not_quit);
	}
}
