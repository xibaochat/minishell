#include "libft.h"

int is_escapted(t_quo *q, const char *s, int i)
{
	int nb_bslash;
	(void)q;

	nb_bslash = 0;
	while (--i >= 0 && s[i] && s[i] == '\\')
		++nb_bslash;
	return (nb_bslash % 2);
}
