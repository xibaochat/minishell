#include "minishell.h"

char *get_cmd_path(char *cmd)
{
	return (ft_strjoin("/bin/", cmd));
}

void exec_command(char **split_input)
{
	char	*cmd_path;
	int		pid;
	int	status;

	cmd_path = get_cmd_path(split_input[0]);
	pid = fork();
	if (pid < 0)
	{
		perror("created failed\n");
		exit(1);
	}
	else if (!pid) //not built in
		execve(cmd_path, split_input,NULL);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			printf("%s\n", strerror(errno));
		if (!WIFEXITED(status))
			printf("%s\n", strerror(errno));
	}
}

int manage_command(char **split_input)
{
	if (!strcmp(split_input[0], "echo"))
		ft_putstr("calling echo builtin\n");
	else if (!strcmp(split_input[0], "pwd"))
		ft_putstr("calling pwd builtin\n");
	else if (!strcmp(split_input[0], "cd"))
		ft_putstr("calling cd builtin\n");
	else if (!strcmp(split_input[0], "env"))
		ft_putstr("calling env builtin\n");
	else if (!strcmp(split_input[0], "export"))
		ft_putstr("calling export builtin\n");
	else if (!strcmp(split_input[0], "unset"))
		ft_putstr("calling unset builtin\n");
	else if (!strcmp(split_input[0], "exit"))
		ft_putstr("calling exit builtin\n");
	else
		exec_command(split_input);
}


char **split_and_execute(char *str, char *sep, int i)
{
	char **arr;
	int j;

	j = 0;
	arr = ft_split(str, sep[i]);
	if (sep[i] == ' ')
		manage_command(arr);
	while (arr[j])
	{
		split_and_execute(arr[j], sep, i + 1);
		j++;
	}
}

void manage_input(void)
{
	char *input;
	int i;
	char sep[4] = ";| ";

	i = 0;
	input = NULL;
	while (get_next_line(0, &input))
	{
		split_and_execute(input, sep, i);
	}
}

int main(int ac, char **av, char **envp)
{
	char **env;

	display_ascii_dude();
	env = ft_envadd(envp, NULL);
	ft_putstr("> ");
	manage_input();
	return (0);
}
