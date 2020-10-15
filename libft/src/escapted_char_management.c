#include "libft.h"

int is_escapted(t_quo *q, const char *s, int i)
{
	int nb_bslash;

	if (q->have_quote && q->single_quote)
		return (0);
	nb_bslash = 0;
	while (--i >= 0 && s[i] && s[i] == '\\')
		++nb_bslash;
	return (nb_bslash % 2);
}

/**
 * Check if current char (=s[i]) is equal to given char (=c)
 * If so, also check that the char is not escaped
*/
int	is_unescapted_c(t_quo *q, const char *s, int i, const char c)
{
	if (s[i] != c)
		return (0);
	if (is_escapted(q, s, i))
		return (0);
	return (1);
}
