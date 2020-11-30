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
			lens--;
			while (lens >= 0 && s[lens] && s[lens] == ' ')
				lens--;
			if (lens < 0 || s[lens] == c)
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
