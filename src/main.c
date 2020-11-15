#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void exec_command(char **split_input, t_mini *sh)
{  
	if (!ft_strcmp(split_input[0], "export") && !sh->is_pipe)
		export(split_input, sh);
	else if (!ft_strcmp(split_input[0], "unset") && !sh->is_pipe)
		unset(split_input, sh);
	else if (!ft_strcmp(split_input[0], "cd") && !sh->is_pipe)
		ft_cd(split_input, sh);
	else if (!ft_strcmp(split_input[0], "exit"))
		ft_exit(split_input, sh);
	else
	{
		sh->last_pid = fork();
		if (sh->last_pid < 0)
		{
			ft_error("Fork failed", errno);
			exit(EXIT_FAILURE);
		}
		else if (!sh->last_pid) //not built in, child process
			child_process(split_input, sh);
		else
			parent_process(sh);
	}
}

void split_and_execute(char *str, char *sep, int i, t_mini *sh)
{
	char **arr;
	int j;

	j = 0;
	arr = ft_split_w_quotes(str, sep[i]);
	if (!arr || !arr[0])
		return;
	if (sep[i] == '|' && ft_tablen(arr) > 1)
	{
		sh->is_pipe = 1;
		exec_command(arr, sh);
		sh->is_pipe = 0;
	}
	else if (sep[i] == ' ')
	{
		check_quote_close(arr, sh);
		if (!sh->last_return)
		{
			replace_var_sub_by_true_value(arr, sh);
			delete_quotes_from_arr(arr);
			delete_slash_from_arr(arr);
			exec_command(arr, sh);
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
	ft_signal(sh);
	while (print_prompt(sh) && get_next_line(0, &input))
	{
		if (is_syntax_error(input, sh))
			continue ;
		sh->exit_v = sh->last_return;
		sh->line = input;
		sh->is_cmd = 1;
		split_and_execute(input, sep, i, sh);
		sh->is_cmd = 0;
		free_str(input);
	}
	ft_putstr_fd("exit", 2);
	free_str(input);
}

int main(int ac, char **av, char **env)
{
	t_mini **sh;

	//manage_signals();
	//sh.last_pid = 0;
	//	show_cat();
	//	show_welcome_mes();
	sh = get_sh();
	init_sh(env, sh);
	if (!ft_find_env(ENV_HOME, (*sh)->env))
		ft_printf(HOME_ERROR, RED, WHITE);
	manage_input(*sh);
	free_var(sh);
	(void)ac;
	(void)av;
	return (0);
}
