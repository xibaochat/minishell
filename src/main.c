#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void split_and_execute(char *str, char *sep, int i, t_mini *sh)
{
	char **arr;
	int j;

	j = 0;
	arr = ft_split_w_quotes(str, sep[i]);
	if (!arr || !arr[0])
		return;
	if (sep[i] == ' ')
		manage_sep_space(arr, sh);
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
	init_sh(env);
	sh = get_sh();
	if (!ft_find_env(ENV_HOME, (*sh)->env))
		ft_printf(HOME_ERROR, RED, WHITE);
	manage_input(*sh);
	free_var(sh);
	return (0);
}
