# include "minishell.h"

void exec_command(char *full_cmd_path, char **split_input, t_mini *sh)
{
	sh->last_pid = fork();
	if (sh->last_pid < 0)
	{
		perror("created failed\n");
		exit(EXIT_FAILURE);
	}
	else if (!sh->last_pid) //not built in, child process
		child_process(full_cmd_path, split_input, sh);
	else
		parent_process(sh);
}

void manage_command(char **split_input, t_mini *sh)
{
	char	*full_cmd_path;

	if (!ft_strcmp(split_input[0], "echo"))
		echo(split_input);
	else if (!ft_strcmp(split_input[0], "pwd"))
		pwd(sh);
	else if (!ft_strcmp(split_input[0], "cd"))
		ft_cd(split_input, sh);
	else if (!ft_strcmp(split_input[0], "env"))
		env(sh);
	else if (!ft_strcmp(split_input[0], "export"))
		export(split_input, sh, 1);
	else if (!ft_strcmp(split_input[0], "unset"))
		unset(split_input, sh);
	else if (!ft_strcmp(split_input[0], "exit"))
		ft_exit(split_input, sh, 2);
	else if (full_cmd_path = get_full_cmd_path(split_input[0], sh))
	{
		exec_command(full_cmd_path, split_input, sh);
		free_str(full_cmd_path);
	}
}

void manage_sep_space(char **arr, t_mini *sh)
{
	check_quote_close(arr, sh);
	if (!sh->last_return)
	{
		replace_var_sub_by_true_value(arr, sh);
		delete_quotes_from_arr(arr);
		delete_slash_from_arr(arr);
		manage_command(arr, sh);
	}
}
