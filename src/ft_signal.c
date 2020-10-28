# include "minishell.h"


void ft_not_quit(int sig)
{
	char **buffer;
	t_mini **sh;

//empty gnl buffer in case we used ctrl_D to provide a eof
	buffer = get_buffer();
	sh = get_sh();
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}// jusqu'a ici
	(*sh)->last_return = 130;
	ft_putstr_w_new_line_fd("", 2);
	if ((*sh)->is_cmd)
	{
		print_prompt(*sh);
		if (!(*sh)->ctrl_c)
			(*sh)->ctrl_c = 1;
	}
	else
		print_prompt(*sh);
}

void ft_signal(t_mini *sh)
{
//receive ctrl-C signal, works like mlx_hook
	signal(SIGINT, ft_not_quit);
}
