#include "minishell.h"

void	free_var(t_mini **sh)
{
	if ((*sh)->env)
		ft_tabfree((*sh)->env);
	free(*sh);
	*sh = NULL;
}
