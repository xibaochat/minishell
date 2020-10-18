# include "libft.h"

int get_len_wo_extra_slash(char *s)
{
	int i;
	int nb_slash;
	int j;

	i = 0;
	j = 0;
	nb_slash = 0;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			while (s[i] && s[i] == '\\')
			{
				i++;
				nb_slash++;
				j++;
			}
		}
		else
			i++;
	}
	return (i - j + (nb_slash / 2));
}

void copy_part_str_wo_slash(char *s, int *i, char *new, int *j)
{
	int nb_slash;
	int k;

	nb_slash = 0;
	while (s[*i] && s[*i] == '\\')
	{
		(*i)++;
		nb_slash++;
	}
	k = nb_slash / 2;
	while (k--)
		new[(*j)++] = '\\';
}

void copy_wo_slash(char *new, char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\\')
			new[j++] = s[i++];
		else
			copy_part_str_wo_slash(s, &i, new, &j);

	}
}

void delete_slash_from_str(char **s)
{
	char *new;
	int final_len;

	final_len = get_len_wo_extra_slash(*s);
	new = ft_strnew(final_len + 1);
	copy_wo_slash(new, *s);
	free(*s);
	*s = new;
}
