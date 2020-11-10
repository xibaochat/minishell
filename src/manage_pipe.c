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
			printf("DEBUG : PIPE FAILED\n");
		sh->last_pid = fork();
		if (sh->last_pid < 0)
			printf("DEBUG : FORK FAILED \n");
		else if (!sh->last_pid)
		{
			close(fd[0]);
			if (i != nb_pipes)
			{
				if (dup2(fd[1], 1) == -1)
					printf("DEBUG SON : DUP2 FAILED\n");
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
					printf("DEBUG SON : DUP2 FAILED\n");
			}
			close(fd[0]);
		//	split_and_execute(arr[i + 1], " ", 0, sh);
		}
	}
}




/*
   void	ft_manage_pipe2(t_mini *sh, char **arr, int *fd_1, int out)
   {
   int	fd_2[2];
   int	status;

   if (pipe(fd_2) == -1)
   printf("DEBUG : PIPE FAILED\n");
   sh->last_pid = fork();
   if (sh->last_pid < 0)
   printf("DEBUG : FORK FAILED \n");
   else if (!sh->last_pid)
   {
   close(fd_1[0]);
   close(fd_2[0]);
   close(fd_1[1]);
   if (!arr[1])
   {
   if (dup2(out, fd_2[1]) == -1)
   printf("DEBUG SON END OF CHAINED PIPE : DUP2 FAILED\n");
   }
   if (dup2(fd_2[1], 1) == -1)
   printf("DEBUG SON : DUP2 FAILED\n");
   printf("SON OF PIPE\n");
   split_and_execute(arr[0], " ", 0, sh);
   close(fd_2[1]);
   exit(1);
   }
   else
   {
   close(fd_2[1]);
   close(fd_1[1]);
   close(fd_2[0]);
   if (dup2(fd_1[0], 0) == -1)
   printf("DEBUG FATHER : DUP2 FAILED\n");
   waitpid(sh->last_pid, &status, 0);
   printf("FATHER OF PIPE\n");
   close(fd_1[0]);
   if (arr[1])
   ft_manage_pipe2(sh, arr + 1, fd_2, out);
   }
   }

   void	ft_manage_pipe(t_mini *sh, char **arr)
   {
   int	fd[2];

   if (pipe(fd) == -1)
   printf("DEBUG : PIPE FAILED\n");
   ft_manage_pipe2(sh, arr, fd, fd[1]);
   }


   void	ft_manage_pipe_2(t_mini *sh, char **arr, int len)
   {
   int	j;
   int	status;
   int	i;
   int	fd[len][2];

   i = -1;
   while (++i <= len)
   pipe(fd[i]);
   j = -1;
   printf("IM HERE\n");
   while (arr[++j])
   {
   printf("arr[%d] = %s\n", j, arr[j]);
   pipe(fd[j]);
   sh->last_pid = fork();
   if (sh->last_pid < 0)
printf("DEBUG : FORK FAILED \n");
else if (!sh->last_pid)
{
	close(fd[j][0]);
	printf("SON OF PIPE : j = %d\n", j);
	if (dup2(fd[j][1], 1) == -1)
		printf("DEBUG SON : DUP2 FAILED\n");
	//write(STDOUT_FILENO, "child\n", 6);
	split_and_execute(arr[j], " ", 0, sh);
	close(fd[j][1]);
	exit(0);
}
else
{
	close(fd[j][1]);
	if (dup2(fd[j][0], 0) == -1)
		printf("DEBUG FATHER : DUP2 FAILED\n");
	waitpid(sh->last_pid, &status, 0);
	printf("FATHER OF PIPE : j = %d\n", j);
	//write(STDOUT_FILENO, "father\n", 7);
	close(fd[j][0]);
}
}
}

void	ft_manage_pipe(t_mini *sh, char **arr)
{
	int	len;

	len = (int)ft_tablen(arr);
	ft_manage_pipe_2(sh, arr, len);
}*/
