#include "libft.h"

static int get_len_wo_quotes(const char *s)
{
	int	i;
	int	len;
	t_quo quo;

	if (!s)
		return (0);
	i = -1;
	len = 0;
	quo = init_quotes_struct();
	while (s[++i])
	{
		manage_struct_quotes(&quo, s, i);
		if ((is_unescapted_c(s, i, '"') && quo.single_quote)
			|| (is_unescapted_c(s, i, '\'') && quo.double_quote)
			|| ((s[i] != '\'' && s[i] != '"') || is_escapted(s, i)))
			++len;
	}
	return (len);
}

static void copy_wo_quotes(char *new, const char *s)
{
	int	i;
	int	j;
	t_quo quo;

	if (!new || !s)
		return ;
	i = -1;
	j = 0;
	quo = init_quotes_struct();
	while (s[++i])
	{
		manage_struct_quotes(&quo, s, i);
		if ((is_unescapted_c(s, i, '"') && quo.single_quote)
			|| (is_unescapted_c(s, i, '\'') && quo.double_quote)
			|| ((s[i] != '\'' && s[i] != '"') || is_escapted(s, i)))
			new[j++] = s[i];
	}
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
