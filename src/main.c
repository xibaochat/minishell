#include "minishell.h"

void exec_command(char **split_input, t_mini *sh)
{
	char	*cmd_path;
	int	status;
	int d;

	cmd_path = NULL;
	sh->last_pid = fork();
	g_sh.last_pid = sh->last_pid;
	if (sh->last_pid < 0)
	{
		perror("created failed\n");
		exit(1);
	}
	else if (!sh->last_pid) //not built in, child process
	{

		// find complete path, ls: /bin/ls
		cmd_path = find_full_binary_path(split_input[0], sh);
		if (!cmd_path)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_w_new_line_fd(split_input[0], 2);
		}
		else
		{
			d = execve(cmd_path, split_input, NULL);
			if (d == -1)
			{
				ft_putstr_fd("Exec format error: ", 2);
				ft_putstr_w_new_line_fd(cmd_path, 2);
				sh->last_return = 127;
			}
		}
	}
	else if (sh->last_pid > 0)
	{
		waitpid(sh->last_pid, &status, 0);
		sh->last_return = status;
		if (WIFSIGNALED(status))
			ft_printf("%s\n", strerror(errno));
		if (!WIFEXITED(status))
			ft_printf("%s\n", strerror(errno));
	}
}

int manage_command(char **split_input, t_mini *sh)
{
	char	*tmp;

	/* tmp = ft_strrmv(split_input[0], SPACE); */
	/* free_str(split_input[0]); */
	/* split_input[0] = tmp; */
	/* ft_putstr("before\n"); */
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
	{
		ft_tabfree(sh->env);
		ft_putstr("exit\n");
		exit(0);
	}
	else
		exec_command(split_input, sh);
}

/*
** ft_split_inc() keeps the separator in the output when splitting
*/

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
			//remove useless quotes and slash
			delete_quotes_from_arr(arr);
			delete_slash_from_arr(arr);
			replace_var_sub_by_true_value(arr, sh);
			manage_command(arr, sh);
		}
	}
	else
		while (arr[j])
		{
			split_and_execute(arr[j], sep, i + 1, sh);
			j++;
		}
}

void manage_input(t_mini *sh)
{
	char *input;
	int i;
	char sep[4] = ";| ";

	i = 0;
	input = NULL;
	while (print_prompt(sh) && get_next_line(0, &input))
	{
		sh->line = input;
		split_and_execute(input, sep, i, sh);
	}
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
