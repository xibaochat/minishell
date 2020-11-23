#include "minishell.h"

int	free_empty_tab(char **arr)
{
	if (!arr[0])
		ft_tabfree(arr);
	return (0);
}

void	free_var(t_mini **sh)
{
	if ((*sh)->env)
		ft_tabfree((*sh)->env);
	free(*sh);
	*sh = NULL;
}
