/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:14 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 17:03:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_waiting_children(t_mini *sh, int *tab, int fd_in)
{
	int	i;
	int	last_ret;

	i = -1;
	while (++i <= sh->nb_pipes)
		waitpid(tab[i], &sh->status, 0);
	read(sh->p[0], &last_ret, sizeof(int));
	close(sh->p[0]);
	close(fd_in);
	free(tab);
	return (last_ret);
}

void	pipe_child(char **arr, int i, t_mini *sh, int fd_in)
{
	int	last_ret;

	dup2(fd_in, STDIN_FILENO);
	close(sh->fd[0]);
	close(sh->p[0]);
	if (i != sh->nb_pipes)
	{
		if (dup2(sh->fd[1], STDOUT_FILENO) == -1)
			ft_error("DUP2 FAILED", errno);
	}
	else
	{
		sh->fd[0] = 0;
		sh->fd[1] = 1;
	}
	last_ret = split_and_execute(arr[i], " ", 0, sh);
	write(sh->p[1], &last_ret, sizeof(int));
	close(sh->p[1]);
	close(sh->fd[1]);
	exit(1);
}

void	pipe_parent(t_mini *sh, int fd_in)
{
	close(fd_in);
	fd_in = dup(sh->fd[0]);
	close(sh->p[1]);
	close(sh->fd[1]);
	close(sh->fd[0]);
	return ;
}

void	ft_piping(t_mini *sh)
{
	if (pipe(sh->p) == -1)
		ft_error("PIPE FAILED", errno);
	if (pipe(sh->fd) == -1)
		ft_error("PIPE FAILED", errno);
	sh->last_pid = fork();
}

/*
** sh->p[2] gets the return_value from child to parent process.
** sh->fd[2] transmits the output from previous pipe to the next one's input.
** fd_in is used to save sh->fd[0] allowing to close(sh->fd[0])
** and use it in the next pipe
*/

int		ft_manage_pipe(t_mini *sh, char **arr)
{
	int	i;
	int	last_ret;
	int	*tab;
	int	fd_in;

	sh->nb_pipes = ft_tablen(arr) - 1;
	tab = malloc(sizeof(int) * (sh->nb_pipes + 1));
	tab[sh->nb_pipes] = 0;
	fd_in = dup(STDIN_FILENO);
	i = -1;
	while (++i <= sh->nb_pipes)
	{
		ft_piping(sh);
		if (sh->last_pid < 0)
			ft_error("FORK FAILED", errno);
		else if (!sh->last_pid)
			pipe_child(arr, i, sh, fd_in);
		else
		{
			pipe_parent(sh, fd_in);
			tab[i] = sh->last_pid;
		}
	}
	last_ret = ft_waiting_children(sh, tab, fd_in);
	return (last_ret);
}
