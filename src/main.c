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

	tmp = ft_strrmv(split_input[0], SPACE);
	free_str(split_input[0]);
	split_input[0] = tmp;
	if (!strcmp(split_input[0], "echo"))
		echo(split_input);
	else if (!strcmp(split_input[0], "pwd"))
		pwd(sh);
	else if (!strcmp(split_input[0], "cd"))
		cd(split_input, sh);
	else if (!strcmp(split_input[0], "env"))
		env(sh);
	else if (!strcmp(split_input[0], "export"))
		export(split_input, sh);
	else if (!strcmp(split_input[0], "unset"))
		unset(split_input, sh);
	else if (!strcmp(split_input[0], "exit"))
		ft_putstr("calling exit builtin\n");
	else
	{
		exec_command(split_input, sh);
	}
}

/*
** ft_split_inc() keeps the separator in the output when splitting
*/

char **split_and_execute(char *str, char *sep, int i, t_mini *sh)
{
	char **arr;
	int j;

	j = 0;
	arr = ft_split_w_quotes(str, sep[i]);
	if (sep[i] == ' ')
		manage_command(arr, sh);
	else
		while (arr[j])
		{
			split_and_execute(arr[j], sep, i + 1, sh);
			j++;
		}
}

int print_prompt(t_mini *sh)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!sh->last_return)
		ft_putstr_fd(GREEN, 2);
	else
		ft_putstr_fd(RED, 2);
	ft_putstr_fd("[", 2);
	ft_printf("%d", sh->last_return);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" : "DEFAULT_COLOR, 2);
	free_str(path);
	return (1);
}

void manage_input(t_mini *sh)
{
	char *input;
	int i;
	char sep[4] = ";| ";

	i = 0;
	input = NULL;
	while (print_prompt(sh) && get_next_line(0, &input))
		split_and_execute(input, sep, i, sh);
}

int main(int ac, char **av, char **env)
{
	t_mini	sh;

	//display_ascii_dude();
	g_sh = sh;
	manage_signals();
	sh.last_pid = 0;
	sh.last_return = 0;
	cpy_env(&sh, env);
	manage_input(&sh);
	return (0);
}
