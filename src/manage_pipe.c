#include "minishell.h"

void	ft_manage_pipe(t_mini *sh, char	**arr)
{
	int	fd[2];
	int	status;
	int	nb_pipes;
	int	i;

	nb_pipes = ft_tablen(arr) - 1;
	i = -1;
	while (++i <= nb_pipes)
	{
		if (pipe(fd) == -1)
			ft_error("PIPE FAILED", errno, sh);
		sh->last_pid = fork();
		if (sh->last_pid < 0)
			ft_error("FORK FAILED", errno, sh);
		else if (!sh->last_pid)
		{
			close(fd[0]);
			if (i != nb_pipes)
			{
				if (dup2(fd[1], 1) == -1)
					ft_error("DUP2 FAILED", errno, sh);
			}
			split_and_execute(arr[i], " ", 0, sh);
			close(fd[1]);
			exit(1);
		}
		else
		{
			waitpid(sh->last_pid, &status, 0);
			close(fd[1]);
			if (i != nb_pipes)
			{
				if (dup2(fd[0], 0) == -1)
					ft_error("DUP2 FAILED", errno, sh);
			}
			close(fd[0]);
		}
	}
}
