#	include "libft.h"

void	show_arr_value(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			ft_putstr_w_new_line(arr[i]);
	}
}
