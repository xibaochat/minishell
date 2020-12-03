#include "libft.h"

/*
**	ft_strrmv removes all char of sep in s and returns the new string
*/

static int	get_new_len(char *s, char *sep)
{
	int	i;
	int	lens;

	i = 0;
	lens = 0;
	while (s[i])
	{
		if (!ft_strchr(sep, s[i]))
			lens++;
		i++;
	}
	return (lens);
}

char	*ft_strrmv(char *s, char *sep)
{
	int		i;
	int		len;
	char	*d;

	i = 0;
	len = get_new_len(s, sep);
	d = ft_strnew(len + 1);
	if (!d)
		return (NULL);
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
