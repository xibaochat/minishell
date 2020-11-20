#include "libft.h"

void	delete_slash_from_arr(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		delete_slash_from_str(&arr[i]);
}
