#include "minishell.h"

int	ft_manage_pipe(t_mini *sh, char	**arr)
{
	int	fd[2];
	int	p[2];
	int	status;
	int	nb_pipes;
	int	i;
	int	last_ret;
	int	pipe_last_ret;

	last_ret = 0;
	pipe_last_ret = 0;
	nb_pipes = ft_tablen(arr) - 1;
	i = -1;
	while (++i <= nb_pipes)
	{
		pipe(p);
		if (pipe(fd) == -1)
			ft_error("PIPE FAILED", errno, sh);
		sh->last_pid = fork();
		if (sh->last_pid < 0)
			ft_error("FORK FAILED", errno, sh);
		else if (!sh->last_pid)
		{
			close(fd[0]);
			close(p[0]);
			if (i != nb_pipes)
			{
				if (dup2(fd[1], 1) == -1)
					ft_error("DUP2 FAILED", errno, sh);
			}
			last_ret = split_and_execute(arr[i], " ", 0, sh);
			write(p[1], &last_ret, sizeof(int));
			close(fd[1]);
			close(p[1]);
			exit(1);
		}
		else
		{
			waitpid(sh->last_pid, &status, 0);
			close(p[1]);
			close(fd[1]);
			if (i != nb_pipes)
			{
				if (dup2(fd[0], 0) == -1)
					ft_error("DUP2 FAILED", errno, sh);
			}
			read(p[0], &last_ret, sizeof(int));
			if (last_ret > pipe_last_ret)
				pipe_last_ret = last_ret;
			close(fd[0]);
			close(p[0]);
		}
	}
	return (pipe_last_ret);
}
