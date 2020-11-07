# include "minishell.h"

void ft_cold_quit(int sig)
{
	t_mini **sh;

	sh = get_sh();
	if ((*sh)->is_cmd == 1)
	{
		(*sh)->last_return = 131;
		ft_putstr_w_new_line_fd("", 2);
	}
	else
		(*sh)->last_return = 0;
}

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
	ft_putstr_w_new_line_fd("", 2);
	(*sh)->last_return = 130;
//	if ((*sh)->is_cmd) // ls -R / in the process of execution
//	{
		print_prompt(*sh);
//		if ((*sh)->ctrl_c == 0)
//			(*sh)->ctrl_c = 1;
//	}
//	else
//		print_prompt(*sh);
}

void ft_signal(t_mini *sh)
{
//receive ctrl-C signal, works like mlx_hook
	signal(SIGINT, ft_not_quit);
	signal(SIGQUIT, ft_cold_quit);
}
