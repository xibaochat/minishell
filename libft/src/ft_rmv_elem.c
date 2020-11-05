#include "libft.h"

/*
** ft_rmv_elem() will copy tab and remove the i-th element from the tab
*/

char	**ft_rmv_elem(char **tab, int i)
{
	int	j;
	int	k;
	char	**dup;

	if (!tab || !tab[0])
		return (NULL);
	if (!(dup = malloc(sizeof(char *) * (ft_tablen(tab) - 1 + 1))))
		return (NULL);
	j = 0;
	k = -1;
	while (tab[++k])
	{
		if (tab[k][0] && k != i)
		{
			if (!(dup[j] = malloc(sizeof(char *) * ft_strlen(tab[k]) + 1)))
				return (NULL);
			ft_memcpy(dup[j], tab[k], ft_strlen(tab[k]));
			dup[j][ft_strlen(tab[k])] = '\0';
		}
		if (k == i)
			j--;
		j++;
	}
	dup[j] = NULL;
	return (dup);
}
