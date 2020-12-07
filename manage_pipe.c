#include "minishell.h"

void	pipe_child(int *fd, char **arr, int i, t_mini *sh)
{
	int	nb_pipes;
	int	last_ret;

	nb_pipes = ft_tablen(arr) - 1;
	close(fd[0]);
	close(sh->p[0]);
	if (i != nb_pipes)
	{
		if (dup2(fd[1], 1) == -1)
			ft_error("DUP2 FAILED", errno);
	}
	else
	{
		fd[0] = 0;
		fd[1] = 1;
	}
	last_ret = split_and_execute(arr[i], " ", 0, sh);
	write(sh->p[1], &last_ret, sizeof(int));
	close(fd[1]);
	close(sh->p[1]);
	exit(1);
}

int	pipe_parent(t_mini *sh, int *fd, int i, int nb_pipes)
{
	int	last_ret;
	int	status;

	last_ret = 0;
	waitpid(sh->last_pid, &status, 0);
	close(sh->p[1]);
	close(fd[1]);
	if (i != nb_pipes)
	{
		if (dup2(fd[0], 0) == -1)
			ft_error("DUP2 FAILED", errno);
	}
	read(sh->p[0], &last_ret, sizeof(int));
	close(fd[0]);
	close(sh->p[0]);
	return (last_ret);
}

void	ft_piping(t_mini *sh, int *fd)
{
	if (pipe(sh->p) == -1)
		ft_error("PIPE FAILED", errno);
	if (pipe(fd) == -1)
		ft_error("PIPE FAILED", errno);
	sh->last_pid = fork();
}

int	ft_manage_pipe(t_mini *sh, char	**arr)
{
	int	fd[2];
	int	nb_pipes;
	int	i;
	int	last_ret;

	last_ret = 0;
	nb_pipes = ft_tablen(arr) - 1;
	i = -1;
	while (++i <= nb_pipes)
	{
		ft_piping(sh, fd);
		if (sh->last_pid < 0)
			ft_error("FORK FAILED", errno);
		else if (!sh->last_pid)
			pipe_child(fd, arr, i, sh);
		else
			last_ret = pipe_parent(sh, fd, i, nb_pipes);
	}
	return (last_ret);
}
