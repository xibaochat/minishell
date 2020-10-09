#include "libft.h"

/*
**	ft_strrmv removes all char of sep in s and returns the new string
*/

char	*ft_strrmv(char *s, char *sep)
{
	int	i;
	int	len;
	char	*d;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (!ft_strchr(sep, s[i]))
			len++;
		i++;
	}
	if (!(d = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (len)
	{
		if (!ft_strchr(sep, *s))
		{
			d[i] = *s;
			len--;
			i++;
		}
		s++;
	}
	d[i] = '\0';
	return (d);
}
