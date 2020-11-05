# include "minishell.h"

void child_process(char **split_input, t_mini *sh)
{
	char	*bin_path;
	char	**tmp;

	tmp = check_for_redir(split_input, sh);
	if (tmp)
		split_input = tmp;
	if (!ft_strcmp(split_input[0], "echo"))
		echo(split_input);
	else if (!ft_strcmp(split_input[0], "pwd"))
		pwd(sh);
	else if (!ft_strcmp(split_input[0], "cd"))
		ft_cd(split_input, sh);
	else if (!ft_strcmp(split_input[0], "env"))
		env(sh);
	else if (!ft_strcmp(split_input[0], "export"))
		export(split_input, sh);
	else if (!ft_strcmp(split_input[0], "unset"))
		unset(split_input, sh);
	else if (!ft_strcmp(split_input[0], "exit"))
		ft_exit(split_input, sh);
	else if (bin_path = get_full_cmd_path(split_input[0], sh))
	{
		execve(bin_path, split_input, sh->env);
		free_str(bin_path);
	}
	//----pour eviter child process in the dead situation-
	// if execve this fnction its self failed, not the result is bad
	// if execve is success, it will kill the fork, child process
	ft_putstr_fd("Exec format error: ", 2);
	ft_putstr_w_new_line_fd(bin_path, 2);
	exit(EXIT_FAILURE);
}

void parent_process(t_mini *sh)
{
	int	status;

	waitpid(sh->last_pid, &status, 0);
	//program execution successful
	if (WIFEXITED(status) && !WEXITSTATUS(status))
		sh->last_return = 0;
	//program terminated normally,but returned a non-zero status
	// ex: touch /filename, you will get error: permission denied
	else if (WIFEXITED(status) && WEXITSTATUS(status))
		sh->last_return = status>>8;
}