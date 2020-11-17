#include "minishell.h"

void	child_process(char **split_input, t_mini *sh)
{
	char	*bin_path;
	char	**tmp;

	if (sh->is_pipe == 1)
	{
		sh->is_pipe = 0;
		ft_manage_pipe(sh, split_input);
	}
	else
	{
		printf("GOT INTO NO PIPE LOOP\n");
		tmp = check_for_redir(split_input, sh);
		if (tmp)
			split_input = tmp;
		if (!ft_strcmp(split_input[0], "echo"))
			echo(split_input);
		else if (!ft_strcmp(split_input[0], "pwd"))
			pwd(sh);
		else if (!ft_strcmp(split_input[0], "env"))
			env(sh);
		else if (!ft_strcmp(split_input[0], "sophie"))
			sophie_la_girafe(ft_atoi(split_input[1]));
		else if ((bin_path = get_full_cmd_path(split_input[0], sh)))
		{
			if (execve(bin_path, split_input, sh->env) == -1)
			{
				//----pour eviter child process in the dead situation-
				// if execve this fnction its self failed, not the result is bad
				// if execve is success, it will kill the fork, child process
				ft_putstr_fd("Exec format error: ", 2);
				ft_putstr_w_new_line_fd(bin_path, 2);
				ft_error("CMD NOT FOUND", errno, sh);
			}
			free_str(bin_path);
		}
	}
	exit(EXIT_SUCCESS);
}

void	parent_process(t_mini *sh)
{
	int	status;

	waitpid(sh->last_pid, &status, 0);
	printf("status = %d\n", status);
	//program execution successful
	if (WIFEXITED(status) && !WEXITSTATUS(status))
	{
		printf("!WEXITSTATUS  : no pb and last return is = <%d>\n", sh->last_return);
		sh->last_return = 0;
	}
	//program terminated normally,but returned a non-zero status
	// ex: touch /filename, you will get error: permission denied
	else if (WIFEXITED(status) && WEXITSTATUS(status))
	{
		sh->last_return = status >> 8;
		printf("WEXITSTATUS  : pb chef ! = <%d>\n", sh->last_return);
	}
}
