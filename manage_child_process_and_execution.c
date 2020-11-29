#include "minishell.h"

// Note concerning the if (execve(...) == -1) control structure :
//----pour eviter child process in the dead situation-
// if execve this fnction its self failed, not the result is bad
// if execve is success, it will kill the fork, child process

int	has_space(char *s)
{
	int		i;
	t_quo	q;

	q = init_quotes_struct();
	i = -1;
	while (s[++i])
	{
		manage_struct_quotes(&q, s, i);
		if (s[i] == ' ' && !q.have_quote)
			return (1);
	}
	return (0);
}

int	child_no_pipe(char **split_input, t_mini *sh)
{
	char	*bin_path;
	char	**new_arr;

	if (!ft_strcmp(split_input[0], "echo"))
		echo(split_input);
	else if (!ft_strcmp(split_input[0], "pwd"))
		pwd(sh);
	else if (!ft_strcmp(split_input[0], "env"))
		env(sh);
	else
	{
		if (has_space(split_input[0]))
		{
			new_arr = ft_split_w_quotes(split_input[0], ' ');
			ft_tabfree(split_input);
			split_input = new_arr;
		}
		bin_path = get_full_cmd_path(split_input[0], sh);
		if (bin_path)
			exec_not_build_in_cmd(bin_path, split_input, sh);
	}
	return (sh->last_return);
}

int	child_process(char **split_input, t_mini *sh)
{
	char	**tmp;

	tmp = NULL;
	if (sh->is_pipe == 1)
	{
		sh->is_pipe = 0;
		sh->last_return = ft_manage_pipe(sh, split_input);
	}
	else
	{
		tmp = maobe_check_for_redir(split_input, sh);
		if (tmp)
			split_input = tmp;
		sh->last_return = child_no_pipe(split_input, sh);
	}
	//ft_printf("-----in child pro %d----\n", sh->last_return);
	return (sh->last_return);
}

int	parent_process(t_mini *sh)
{
	int	status;

	waitpid(sh->last_pid, &status, 0);
	//program execution successful
	if (WIFEXITED(status) && !WEXITSTATUS(status))
		sh->last_return = 0;
	//program terminated normally,but returned a non-zero status
	// ex: touch /filename, you will get error: permission denied
	else if (WIFEXITED(status) && WEXITSTATUS(status))
		sh->last_return = status >> 8;
	//ft_printf("-----in papa pro %d----\n", sh->last_return);
	return (sh->last_return);
}

int	ft_forking(char **split_input, t_mini *sh)
{
	int	last_ret_child;
	int	last_ret_parent;

	last_ret_child = 0;
	last_ret_parent = 0;
	sh->last_pid = fork();
	if (sh->last_pid < 0)
	{
		ft_error("Fork failed", errno, sh);
		exit(EXIT_FAILURE);
	}
	else if (!sh->last_pid) //not built in, child process
	{
		last_ret_child = child_process(split_input, sh);
		exit(sh->last_return);
	}
	else
		last_ret_parent = parent_process(sh);
	return (ft_max(last_ret_child, last_ret_parent));
}
