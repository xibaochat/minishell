#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void exec_command(char *full_cmd_path, char **split_input, t_mini *sh)
{
	int	status;

	sh->last_pid = fork();
	g_sh.last_pid = sh->last_pid;
	if (sh->last_pid < 0)
	{
		perror("created failed\n");
		exit(EXIT_FAILURE);
	}
	else if (!sh->last_pid) //not built in, child process
	{
		execve(full_cmd_path, split_input, sh->env);
		// if execve this fnction its self failed, not the result is bad
		// if execve is success, it will kill the fork, child process
		ft_putstr_fd("Exec format error: ", 2);
		ft_putstr_w_new_line_fd(full_cmd_path, 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(sh->last_pid, &status, 0);
		sh->last_return = status>>8;
		ft_printf("status id %d\n", status>>8);
	}
}

int manage_command(char **split_input, t_mini *sh)
{
	char	*full_cmd_path;

	if (!ft_strcmp(split_input[0], "echo"))
		echo(split_input);
	else if (!ft_strcmp(split_input[0], "pwd"))
		pwd(sh);
	else if (!ft_strcmp(split_input[0], "cd"))
		cd(split_input, sh);
	else if (!ft_strcmp(split_input[0], "env"))
		env(sh);
	else if (!ft_strcmp(split_input[0], "export"))
		export(split_input, sh);
	else if (!ft_strcmp(split_input[0], "unset"))
		unset(split_input, sh);
	else if (!ft_strcmp(split_input[0], "exit"))
		ft_exit(split_input, sh);
	else if (full_cmd_path = get_full_cmd_path(split_input[0], sh))
		exec_command(full_cmd_path, split_input, sh);
}

void split_and_execute(char *str, char *sep, int i, t_mini *sh)
{
	char **arr;
	int j;

	j = 0;
	arr = ft_split_w_quotes(str, sep[i]);
	if (!arr || !arr[0])
		return;
	if (sep[i] == ' ')
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
	else
		while (arr[j])
		{
			split_and_execute(arr[j], sep, i + 1, sh);
			j++;
		}
	ft_tabfree(arr);
}

void manage_input(t_mini *sh)
{
	char *input;
	int i;
	char sep[4] = ";| ";

	i = 0;
	input = NULL;
	ft_signal(1, sh);
	while (print_prompt(sh) && get_next_line(0, &input))
	{
		sh->line = input;
		split_and_execute(input, sep, i, sh);
	}
	ft_putstr_w_new_line(input);
}

int main(int ac, char **av, char **env)
{
	t_mini	sh;

	//g_sh = sh;
	//manage_signals();
	//sh.last_pid = 0;
//	show_cat();
//	show_welcome_mes();
	sh.last_return = 0;
	cpy_env(&sh, env);
	if (!ft_find_env(ENV_HOME, sh.env))
		ft_printf(HOME_ERROR, RED, WHITE);
	manage_input(&sh);
	return (0);
}
