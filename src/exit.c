#include "minishell.h"

static int	has_alpha(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_isalpha(s[i]))
			return (1);
		if (i > 0 && ((s[i] == '+' || s[i] == '-') || !ft_isalpha(s[i])))
			return (1);
	}
	return (0);
}

static void	fst_arg_is_alpha(char *s, t_mini *sh)
{
	if (s && has_alpha(s))
	{
		ft_printf("exit\n./minishell: exit: %s : ", s);
		ft_printf("numeric argument required\n");
		ft_tabfree(sh->env);
		exit(255);
	}
}

static void	ft_check_exit(char **s, t_mini *sh)
{
	fst_arg_is_alpha(s[1], sh);
	ft_tabfree(sh->env);
	ft_putstr("exit\n");
	exit(ft_atoi(s[1]));
}

void	ft_exit(char **split_input, t_mini *sh)
{
	int	tab_len;

	tab_len = ft_tablen(split_input);
	if (tab_len > 2)
	{
		fst_arg_is_alpha(split_input[1], sh);
		ft_putstr_fd("./minishell: exit: too many arguments\n", 2);
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
