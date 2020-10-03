#include "minishell.h"

int has_quote_in_str(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return(1);
	}
	return (0);
}

int get_lens_without_quote(char *s)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			j++;
	}
	return (j);
}

char *rm_quote_in_str(char *s)
{
	int i;
	int j;
	int k;
	char *str;

	i = -1;
	k = 0;
	if (has_quote_in_str(s))
	{
		j = get_lens_without_quote(s);
		str = ft_strnew(j + 1);
		while (s[++i])
		{
			if (s[i] != '\'' && s[i] != '\"')
				str[k++] = s[i];
		}
		return (str);
	}
	else
		return (s);
}
