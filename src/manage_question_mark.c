# include "minishell.h"

/*if the char apres $ is ?*/
int next_char_is_question_mark(char *s, int i)
{
	return (s[i + 1] && s[i + 1] == '?');
}

/*replace $? by exit value  in the str*/
void replace_question_mark_by_exit_value(char **str, int i, int n, t_mini *sh)
{
	char *s;
	int nb_lens;
	char *s1;

	s1 = ft_itoa(n);
	nb_lens = get_nb_size(n);
	s = ft_strnew(ft_strlen(*str) - 1 + nb_lens);
	ft_strncat(s, *str, i);
	ft_strcat(s, s1);
	free_str(s1);
	if ((*str)[i + nb_lens + 1])
		ft_strncat(s, (*str) + i + 2, ft_strlen(*str) - i - 2);
	free_str(*str);
	*str = s;
}

void manage_question_mark(char **str, int *i, int exit_value, t_mini *sh)
{
	replace_question_mark_by_exit_value(str, *i, exit_value, sh);
	*i += get_nb_size(exit_value);
}
