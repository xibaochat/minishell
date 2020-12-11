#include "minishell.h"

static int	has_alpha(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_isalpha(s[i]))
			return (1);
//		if (i > 0 && ((s[i] == '+' || s[i] == '-')))
		if (i > 0 && (s[i] != ' ') && !ft_isdigit(s[i]))
			return (1);
	}
	return (0);
}

static int	ft_check_exit(char **s)
{
	if (s[1] && ft_strlen(s[1]) > 20)
		return (1);
	if ((s[1][0] != '+' && s[1][0] != '-' && !ft_isdigit(s[1][0]))
		|| has_alpha(&s[1][1]))
		return (1);
	if ((s[1][0] == '+' || s[1][0] == '-') && !s[1][1])
		return (1);
	if ((s[1][0] != '-' && ft_atoi(s[1]) < 0)
		|| (s[1][0] == '-' && ft_atoi(s[1]) > 0))
		return (1);
	return (0);
}

void	ft_exit(char **split_input, t_mini *sh)
{
	int	tab_len;

	tab_len = ft_tablen(split_input);
	if (tab_len == 1)
	{
		ft_tabfree(sh->env);
//		ft_putstr("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (tab_len > 2)
	{
		ft_putstr_fd("./minishell: exit: too many arguments\n", 2);
		sh->last_return = 1;
	}
	else if (tab_len == 2)
	{
		ft_tabfree(sh->env);
		if (ft_check_exit(split_input))
		{
			ft_printf("exit\n./minishell: exit: %s : ", split_input[1]);
			ft_printf("numeric argument required\n");
			exit(2);
		}
		else
		{
//			ft_putstr("exit\n");
			exit(ft_atoi(split_input[1]));
		}
	}
}
