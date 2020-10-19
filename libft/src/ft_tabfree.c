# include "libft.h"

void	ft_tabfree(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (tab)
	{
		while (tab[i])
			i++;
		while (j < i && tab[j])
			free_str(tab[j++]);
		free(tab);
		tab = NULL;
	}
}
