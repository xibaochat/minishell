#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	exec_command(char **split_input, t_mini *sh)
{
	int	last_ret_child;
	int	last_ret_parent;
//	int	p[2];

	last_ret_child = 0;
	last_ret_parent = 0;
//	pipe(p);
	if (!ft_strcmp(split_input[0], "export") && !sh->is_pipe)
		export(split_input, sh);
	else if (!ft_strcmp(split_input[0], "unset") && !sh->is_pipe)
		unset(split_input, sh);
	else if (!ft_strcmp(split_input[0], "cd") && !sh->is_pipe)
	{
		ft_cd(split_input, sh);
//		ft_printf("cd %d\n", sh->last_return);
	}
	else if (!ft_strcmp(split_input[0], "exit"))
		ft_exit(split_input, sh);
	else
	{
		sh->last_pid = fork();
		if (sh->last_pid < 0)
		{
			ft_error("Fork failed", errno, sh);
			exit(EXIT_FAILURE);
		}
		else if (!sh->last_pid) //not built in, child process
		{
			last_ret_child = child_process(split_input, sh);
//			ft_printf("last_ret_child %d", last_ret_child);
//			write(p[1], &last_ret_child, sizeof(int));
			exit(sh->last_return);
//			exit(EXIT_SUCCESS);
		}
		else
		{
			last_ret_parent = parent_process(sh);
		}
	}
//	read(p[0], &last_ret_child, sizeof(int));
//	ft_printf("here %d %d %d\n", last_ret_child, last_ret_parent , ft_max(last_ret_child, last_ret_parent));
	return (ft_max(last_ret_child, last_ret_parent));
}

int	split_and_execute(char *str, char *sep, int i, t_mini *sh)
{
	char	**arr;
	int		j;
	int	last_ret;

	j = 0;
	last_ret = 0;
	arr = ft_split_w_quotes(str, sep[i]);
	if (!arr || !arr[0])
		return (0);
	if (sep[i] == '|' && ft_tablen(arr) > 1)
	{
		sh->is_pipe = 1;
		last_ret = exec_command(arr, sh);
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
			last_ret = exec_command(arr, sh);
		}
	}
	else
		while (arr[j])
		{
			/* show_arr_value(arr); */
			/* ft_printf("%c j is %d\n", sep[i], j); */
//			if ((sh->last_return = split_and_execute(arr[j], sep, i + 1, sh)))
//				last_ret = sh->last_return;
			sh->last_return = split_and_execute(arr[j], sep, i + 1, sh);
			sh->exit_v = sh->last_return;
			j++;
		}
	if (last_ret > sh->last_return)
		sh->last_return = last_ret;
//	ft_printf("last return is %d\n", sh->last_return);
	ft_tabfree(arr);
	return (sh->last_return);
}

void	manage_input(t_mini *sh)
{
	char	*input;
	int		i;
	char	sep[4] = ";| ";

	i = 0;
	input = NULL;
	ft_signal(sh);
//	while (print_prompt(sh) && get_next_line(0, &input))
	while (get_next_line(0, &input))
	{
		if (is_syntax_error(input, sh))
			continue ;
		sh->exit_v = sh->last_return;
		sh->line = input;
		sh->is_cmd = 1;
		sh->last_return = split_and_execute(input, sep, i, sh);
		sh->is_cmd = 0;
		free_str(input);
	}
	ft_putstr_fd("exit", 2);
	free_str(input);
}

int	main(int ac, char **av, char **env)
{
	t_mini	**sh;

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
