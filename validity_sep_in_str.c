#include "minishell.h"

static int	is_all_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i])
		return (1);
	return (0);
}

int	sep_is_between_space(char *s, char c)
{
	int		lens;
	t_quo	q;

	lens = ft_strlen(s);
	q = init_quotes_struct();
	while (--lens >= 0)
	{
		manage_struct_quotes(&q, s, lens);
		if (s[lens] == c && !q.have_quote)
		{
			if (!lens)
				return (1);
			lens--;
			while (lens >= 0 && s[lens] && s[lens] == ' ')
			{
				manage_struct_quotes(&q, s, lens);
				lens--;
			}
			manage_struct_quotes(&q, s, lens);
			if ((lens < 0 || s[lens] == c) && !q.have_quote)
				return (1);
		}
	}
	return (0);
}

static int	display_error_and_free(char **arr_tmp, char c)
{
	ft_tabfree(arr_tmp);
	redirection_message_err(c);
	return (1);
}

int	sep_in_str_is_invalid(char *str, char c)
{
	char	**arr_tmp;
	int		i;
	int		nb;

	arr_tmp = ft_split_w_quotes(str, c);
	if (!arr_tmp || sep_is_between_space(str, c))
		return (display_error_and_free(arr_tmp, c));
	else
	{
		i = -1;
		nb = 0;
		while (arr_tmp[++i])
		{
			if (is_all_space(arr_tmp[i]))
				nb++;
		}
		if (nb > 1)
			return (display_error_and_free(arr_tmp, c));
	}
	ft_tabfree(arr_tmp);
	return (0);
}
