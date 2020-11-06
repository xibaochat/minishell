#include "minishell.h"

void	ft_manage_pipe_2(t_mini *sh, char **arr, int len)
{
	int	j;
	int	status;
	int	i;
	int	fd[len][2];

	j = -1;
	i = -1;
	while (++i <= len)
		pipe(fd[i]);
	while (arr[++j])
	{
		pipe(fd[j]);
		sh->last_pid = fork();
		if (sh->last_pid < 0)
			printf("DEBUG : FORK FAILED \n");
		else if (!sh->last_pid)
		{
			close(fd[j][0]);
			write(STDOUT_FILENO, "child\n", 6);
			printf("SON OF PIPE\n");
			if (dup2(fd[j][1], 1) == -1)
				printf("DEBUG SON : DUP2 FAILED\n");
			split_and_execute(arr[j], " ", 0, sh);
			close(fd[j][1]);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[j][1]);
			waitpid(sh->last_pid, &status, 0);
			printf("FATHER OF PIPE\n");
			write(STDOUT_FILENO, "father\n", 7);
			if (dup2(fd[j][0], 0) == -1)
				printf("DEBUG FATHER : DUP2 FAILED\n");
			close(fd[j][0]);
		}
	}
}

void	ft_manage_pipe(t_mini *sh, char **arr)
{
	int	len;

	len = (int)ft_tablen(arr);
	ft_manage_pipe_2(sh, arr, len);
}
