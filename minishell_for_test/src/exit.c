#include "minishell.h"

static int	has_alpha(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_isalpha(s[i]))
			return (1);
	}
	return (0);
}

static void	ft_check_exit(char **s, t_mini *sh)
{
	if (has_alpha(s[1]))
	{
		ft_printf("exit\n./minishell: exit: %s : ", s[1]);
		ft_printf("numeric argument required\n");
		ft_tabfree(sh->env);
		exit(255);
	}
	else
	{
		ft_tabfree(sh->env);
		exit(ft_atoi(s[1]));
	}
}

void	ft_exit(char **split_input, t_mini *sh)
{
	int	tab_len;

	tab_len = ft_tablen(split_input);
	if (tab_len > 2)
	{
		ft_putstr_fd("./Minishell: exit: too many arguments\n", 2);
		sh->last_return = 1;
	}
	else if (tab_len == 2)
		ft_check_exit(split_input, sh);
	else
	{
		ft_tabfree(sh->env);
		exit(EXIT_SUCCESS);
	}
}
