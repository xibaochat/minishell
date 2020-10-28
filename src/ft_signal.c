# include "minishell.h"


void ft_not_quit(int sig)
{
	char **buffer;

//empty gnl buffer in case we used ctrl_D to provide a eof
	buffer = get_buffer();
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}// jusqu'a ici
	g_sh.last_return = 130;
	ft_putstr_w_new_line_fd("", 2);
	if (g_sh.is_cmd)
	{
		if (g_sh.ctrl_c)
			g_sh.ctrl_c = 0;
		print_prompt(&g_sh);
		g_sh.ctrl_c = 1;
	}
	else
		print_prompt( &g_sh);
}

void ft_signal(t_mini *sh)
{
//receive ctrl-C signal, works like mlx_hook
	signal(SIGINT, ft_not_quit);
}
