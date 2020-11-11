# include "minishell.h"

static void pipe_parent_process(pid_t pid, t_mini *sh)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && !WEXITSTATUS(status))
        sh->last_return = 0;
	else if (WIFEXITED(status) && WEXITSTATUS(status))
        sh->last_return = status>>8;
}

void give_read_fd_to_input_fd(int i, int nb_cmd, int *input_fd, int *pipe_fd)
{
    if (i != nb_cmd)
		*input_fd = pipe_fd[READ_END];
	else
		close(pipe_fd[READ_END]);
}

void dup_child_rw_pipe(int i, int nb_cmd, int input_fd, int *pipe_fd)
{
    if (i > 0)
		dup2(input_fd, STDIN_FILENO);
    if (i != nb_cmd)
	{
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		//close(pipe_fd[WRITE_END]);
		close(pipe_fd[READ_END]);
	}
	if (input_fd != -1)
		close(input_fd);
}

void manage_pipe(int i, int nb_cmd, char **arr, t_mini *sh)
{
    char *full_cmd;
	char **arr_output;
    pid_t pid;
    int input_fd = -1;
    int pipe_fd[2];

    full_cmd = NULL;
    while (++i <= nb_cmd)
    {
		if (i < nb_cmd)
			pipe(pipe_fd);
		else
		{
			pipe_fd[0] = 0;
			pipe_fd[1] = 1;
		}
		arr_output = ft_split_w_quotes(arr[i], ' ');
		replace_var_sub_by_true_value(arr_output, sh);
		delete_quotes_from_arr(arr_output);
		delete_slash_from_arr(arr_output);
		if (!ft_strcmp(arr_output[0], "echo"))
			pipe_echo(arr_output, pipe_fd);
		else if (!ft_strcmp(arr_output[0], "pwd"))
			pipe_pwd(pipe_fd, sh);
		else if (!ft_strcmp(arr_output[0], "cd"))
			ft_cd(arr_output, sh);
		else if (!ft_strcmp(arr_output[0], "env"))
			pipe_env(pipe_fd, sh);
		else if (!ft_strcmp(arr_output[0], "export"))
			export(arr_output, sh, pipe_fd[1]);
		else if (!ft_strcmp(arr_output[0], "unset"))
			unset(arr_output, sh);
		else if (!ft_strcmp(arr_output[0], "exit"))
		{
//			if (!nb_cmd)
				ft_exit(arr_output, sh, pipe_fd[1]);
//			else
//				continue;
		}
		else if (full_cmd = get_full_cmd_path(arr_output[0], sh))
		{
			pid = fork();
			if (pid < 0)
			{
				perror("created failed\n");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				dup_child_rw_pipe(i, nb_cmd, input_fd, pipe_fd);
				execve(full_cmd, arr_output, sh->env);
				ft_putstr_fd("Exec format error: ", STDERR_FILENO);
				ft_putstr_w_new_line_fd(arr_output[0], STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
			else
				pipe_parent_process(pid, sh);
		}
		if (input_fd != -1)
			close(input_fd);
		if (i < nb_cmd)
		{
			close(pipe_fd[WRITE_END]);
			give_read_fd_to_input_fd(i, nb_cmd, &input_fd, pipe_fd);
		}
	}
}

void manage_pipe_space(char **arr, t_mini *sh)
{
	int nb_cmd;
	int i;

	i = -1;
//	replace_var_sub_by_true_value(arr, sh);
//	delete_quotes_from_arr(arr);
//	delete_slash_from_arr(arr);
	nb_cmd = ft_tablen(arr) - 1;
	manage_pipe(i, nb_cmd, arr, sh);
}
