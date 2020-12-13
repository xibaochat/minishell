/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:41:48 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 17:03:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cold_quit(int sig)
{
	t_mini	**sh;

	sh = get_sh();
	if ((*sh)->is_cmd == 1)
	{
		(*sh)->last_return = 131;
		ft_putstr_w_new_line_fd("Quit (core dumped)", STDERR_FILENO);
	}
	else
		(*sh)->last_return = 0;
	(void)sig;
}

/*
** "buffer = get_buffer()" : empty gnl buffer in case
** we use ctrl_D to provide a EOF
** "if ((*sh)->is_cmd)" // ls -R / in the process of execution
*/

void	ft_not_quit(int sig)
{
	char	**buffer;
	t_mini	**sh;

	buffer = get_buffer();
	sh = get_sh();
	(*sh)->last_return = 130;
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	ft_putstr_w_new_line_fd("", STDERR_FILENO);
	if ((*sh)->is_cmd)
	{
		print_prompt(*sh);
		if ((*sh)->ctrl_c == 0)
			(*sh)->ctrl_c = 1;
	}
	else
		print_prompt(*sh);
	(void)sig;
}

void	ft_signal(t_mini *sh)
{
	signal(SIGINT, ft_not_quit);
	signal(SIGQUIT, ft_cold_quit);
	(void)sh;
}
