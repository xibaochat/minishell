# include "libft.h"

char *ft_malloc_and_copy(char *src)
{
	int lens;
	char *str;

	if (src)
	{
		lens = ft_strlen(src);
		str = ft_strnew(lens + 1);
		ft_strncat(str, src, lens);
		return (str);
	}
	return (NULL);
}
