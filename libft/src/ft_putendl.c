#	include "libft.h"

void	ft_putendl(char *str)
{
	if (!str)
		return ;
	ft_putstr(str);
	ft_putchar('\n');
}
