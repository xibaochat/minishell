#include "minishell.h"

char *get_cmd_path(char *cmd)
{
	return (ft_strjoin("/bin/", cmd));
}

void exec_command(char **split_input, t_mini *sh)
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
		execve(cmd_path, split_input, sh->env);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			printf("%s\n", strerror(errno));
		if (!WIFEXITED(status))
			printf("%s\n", strerror(errno));
	}
}

int manage_command(char **split_input, t_mini *sh)
{
	if (!strcmp(split_input[0], "echo"))
		ft_putstr("calling echo builtin\n");
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
		exec_command(split_input, sh);
}

char **split_and_execute(char *str, char *sep, int i, t_mini *sh)
{
	char **arr;
	int j;

	j = 0;
	arr = ft_split(str, sep[i]);
	if (sep[i] == ' ')
		manage_command(arr, sh);
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
	while (get_next_line(0, &input))
	{
		split_and_execute(input, sep, i, sh);
	}
}

int main(int ac, char **av, char **envp)
{
	t_mini	sh;

	//display_ascii_dude();
	sh.env = NULL;
	ft_envadd(envp, NULL, &sh);
	ft_putstr("> ");
	manage_input(&sh);
	return (0);
}
