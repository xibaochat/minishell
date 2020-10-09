#include "libft.h"

/*
** ft_split_inc() includes the separators in the output
*/

int	count_let(char *s, char *sep)
{
	int	let;

	let = 0;
	while (*s)
	{
		while (!ft_strchr(sep, *s))
		{
			let++;
			s++;
		}
		while (ft_strchr(sep, *s))
		{
			let++;
			s++;
		}
		break ;
	}
	return (let);
}

int	count_word(char *s, char *sep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (!ft_strchr(sep, s[i]) && s[i])
			i++;
		while (ft_strchr(sep, s[i]) && s[i])
			i++;
		count++;
	}
	return (count);
}

char	**ft_split_inc(char *s, char *sep)
{
	int	let;
	int	word;
	int	i;
	int	j;
	char	**tab;

	s = ft_strtrim(s, sep);
	word = count_word(s, sep);
	if (!(tab = malloc(sizeof(char *) * (word + 1))))
		return (NULL);
	i = -1;
	while (++i < word)
	{
		let = count_let(s, sep);
		if (!(tab[i] = malloc(sizeof(char) * (let + 1))))
			return (NULL);
		j = 0;
		while (j < let)
		{
			tab[i][j] = *s;
			s++;
			j++;
		}
		tab[i][j] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}
