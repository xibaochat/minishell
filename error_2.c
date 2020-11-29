#include "minishell.h"

int	cmd_exists(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != ';' && !ft_strchr(SPACE, s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	empty_cmd(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && arr[i + 1])
	{
		if (!cmd_exists(arr[i]))
		{
			ft_printf("syntax error near unexpected token ';'\n");
			ft_tabfree(arr);
			return (1);
		}
		i++;
	}
	return (0);
}
