#include "libft.h"

static int get_len_wo_quotes(const char *s)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	if (!s)
		return (0);
	while (s[++i])
		if (s[i] != '"')
			++len;
	return (len);
}

static void copy_wo_quotes(char *new, const char *s)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != '"')
			new[j++] = s[i];
}

void delete_quotes_from_s(char **s)
{
	int		final_len;
	char	*new;

	final_len = get_len_wo_quotes(*s);
	new = ft_strnew(final_len + 1);
	copy_wo_quotes(new, *s);
	free_str(*s);
	*s = new;
}
