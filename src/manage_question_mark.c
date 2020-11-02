# include "minishell.h"

void manage_question_mark(char **str, int j, int n, t_mini *sh)
{
	char *s;
	int nb_lens;
	char *s1;

	s1 = ft_itoa(n);
	nb_lens = get_nb_digit(n);
	s = ft_strnew(ft_strlen(*str) - 1 + nb_lens);
	ft_strncat(s, *str, j);
	ft_strcat(s, s1);
	free_str(s1);
	if ((*str)[j + nb_lens + 1])
		ft_strncat(s, (*str) + j + 2, ft_strlen(*str) - j - 2);
	free_str(*str);
	*str = s;
}
