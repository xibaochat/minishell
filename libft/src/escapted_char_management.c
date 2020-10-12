#include "libft.h"

int is_escapted(const char *s, int i)
{
	int nb_bslash;

	nb_bslash = 0;
	while (--i >= 0 && s[i] && s[i] == '\\')
		++nb_bslash;
	return (nb_bslash % 2);
}


int	is_unescapted_c(const char *s, int i, const char c)
{
	if (s[i] != c)
		return (0);
	if (is_escapted(s, i))
		return (0);
	return (1);
}
