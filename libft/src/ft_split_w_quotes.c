#include "libft.h"

static int		get_nb_words(char *str, char c)
{
	int			i;
	int			nb_words;
	t_quo		quo;

	i = 0;
	nb_words = 0;
	quo = init_quotes_struct();
	while (str[i])
	{
		manage_struct_quotes(&quo, str, i);
		if (((!i && (str[i] != c)) ||
			 (i > 0 &&
			  is_unescapted_c(&quo, str, i - 1, c) &&
			  !is_unescapted_c(&quo, str, i, c) &&
			  !(quo.have_quote))))
			nb_words++;
		i++;
	}
	return (nb_words);
}

static int		get_word_len(char *str, int i, char sep)
{
	int		lens;
	t_quo	quo;

	lens = 0;
	quo = init_quotes_struct();
	while (str[i] && (!is_unescapted_c(&quo, str, i, sep) || quo.have_quote))
	{
		manage_struct_quotes(&quo, str, i);
		i++;
		lens++;
	}
	return (lens);
}

char			**split_into_tab(char **arr, char *str, char sep)
{
	int			i;
	int			j;
	int			k;
	int			lens;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
		{
			lens = get_word_len(str, i, sep);
			arr[j] = (char *)malloc(lens + 1);
			while (str[i] && lens--)
				arr[j][k++] = str[i++];
			arr[j][k] = '\0';
			arr[++j] = NULL;
		}
	}
	return (arr);
}

static char		**empty_arr(void)
{
	char		**res;

	res = (char **)malloc(sizeof(char *));
	res[0] = NULL;
	return (res);
}

char			**ft_split_w_quotes(char const *s, char c)
{
	char		*str;
	int			words_nb;
	char		**arr;

	str = (char *)s;
	arr = NULL;
	if (!str || !str[0])
		return (empty_arr());
	words_nb = get_nb_words(str, c);
	if (!words_nb)
		return (empty_arr());
	arr = (char **)malloc(sizeof(char *) * (words_nb + 1));
	if (!arr)
		return (NULL);
	arr[words_nb] = NULL;
	arr = split_into_tab(arr, str, c);
	/* ft_printf("-------------- START for [%c]\n", c); */
	/* for (int k = 0; arr[k]; k++) */
	/* 	ft_printf("### .%s.\n", arr[k]); */
	/* ft_printf("-------------- END for [%c]\n", c); */
	return (arr);
}
