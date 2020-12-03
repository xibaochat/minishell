#	include "libft.h"

void	ft_tabfree(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free_str(tab[i]);
		free(tab);
		tab = NULL;
	}
}
