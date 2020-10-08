#include "minishell.h"

void	free_str(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}
