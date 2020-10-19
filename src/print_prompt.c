# include "minishell.h"

int print_prompt(t_mini *sh)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!sh->last_return)
		ft_putstr_fd(GR, 2);
	else
		ft_putstr_fd(RED, 2);
	ft_putstr_fd("[", 2);
	ft_printf("%d", sh->last_return);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(" : "DF, 2);
	free_str(path);
	return (1);
}
