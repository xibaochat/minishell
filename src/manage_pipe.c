#include "minishell.h"

void	ft_manage_pipe(t_mini *sh, char **arr)
{
	int	j;
	int	len;
	int	status;

	j = -1;
	len = (int)ft_tablen(arr);
	while (arr[++j])
	{
		pipe(sh->p);
		sh->last_pid = fork();
		if (sh->last_pid < 0)
			printf("DEBUG : FORK FAILED \n");
		else if (!sh->last_pid)
		{
			close(sh->p[0]);
			printf("SON OF PIPE\n");
			if (dup2(sh->p[1], 1) == -1)
				printf("DEBUG SON : DUP2 FAILED\n");
			split_and_execute(arr[j], " ", 0, sh);
			close(sh->p[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(sh->p[1]);
			waitpid(sh->last_pid, &status, 0);
			printf("FATHER OF PIPE\n");
			if (dup2(sh->p[0], 0) == -1)
				printf("DEBUG FATHER : DUP2 FAILED\n");
			close(sh->p[0]);
		}
	}
}
