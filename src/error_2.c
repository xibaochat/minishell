#include "minishell.h"

int	empty_cmd(char **arr)
{
	int	i;
	int	j;
	int	empty;

	i = 0;
	empty = 1;
	while (arr[i])
	{
		j = 0;
		empty = 1;
		while (arr[i][j])
		{
			if (arr[i][j] && arr[i][j] != ';' && !ft_strchr(SPACE, arr[i][j]))
				empty = 0;
			j++;
		}
		i++;
		if (empty)
			break ;
	}
	if (empty)
	{
		ft_printf("syntax error near unexpected token ';'\n");
		ft_tabfree(arr);
		return (1);
	}
	return (0);
}
