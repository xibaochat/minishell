#include "libft.h"

void delete_quotes_from_arr(char **arr)
{
	int i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		delete_quotes_from_s(&arr[i]);
}
