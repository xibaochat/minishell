#include "libft.h"

int	no_newline_in_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (0);
	return (1);
}
