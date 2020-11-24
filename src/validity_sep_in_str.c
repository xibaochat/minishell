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
	int	lens;

	lens = ft_strlen(s);
	while (--lens >= 0)
	{
		if (s[lens] == c)
		{
			if (!lens)
				return (1);
			while (s[--lens] && s[lens] == ' ')
				;
			if (s[lens] == c || !lens)
				return (1);
		}
	}
	return (0);
}

int	sep_in_str_is_invalid(char *str, char c)
{
	char	**arr_tmp;
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	arr_tmp = ft_split_w_quotes(str, c);
	if (!arr_tmp || sep_is_between_space(str, c))
	{
		ft_tabfree(arr_tmp);
		ft_printf("syntax error near unexpect\
ed token `%c'\n", c);
		return (1);
	}
	else
	{
		while (arr_tmp[i])
		{
			if (is_all_space(arr_tmp[i]))
			{
				/* ft_printf("syntax error near unexpected token `%c'\n", c); */
				/* ft_tabfree(arr_tmp); */
				/* return (1); */
				nb++;
			}
			i++;
		}
		if (nb > 1)
		{
			ft_printf("syntax error near unexpected token `%c'\n", c);
			ft_tabfree(arr_tmp);
			return (1);
		}
	}
	ft_tabfree(arr_tmp);
	return (0);
}
