# include "minishell.h"

static int is_invalid_varname(t_quo *q, const char *s, int i)
{
	return (s[i] &&
            (is_unescapted_c(q, s, i, '$')
             || is_unescapted_c(q, s, i, '?')
             || is_unescapted_c(q, s, i, '\\')
             || is_unescapted_c(q, s, i, SINGLE)
     	     || is_unescapted_c(q, s, i, DOUBLE)));
}

int get_varname_len(const char *s, int i)
{
	int len;
	t_quo q;

	len = 0;
	q = init_quotes_struct();
	while (s[++i])
	{
		manage_struct_quotes(&q, s, i);
		if (is_invalid_varname(&q, s, i))
			break;
		++len;
	}
	return (len);
}

int replace_var_condition(t_quo *q, char *s, int i)
{
	if (s[i + 1])
	{
		if (q->double_quote && !get_varname_len(s, i))
			return (0);
		return (1);
	}
	return (0);
}

void manage_substitution_in_str(t_mini *sh, char **str)
{
	int i;
	t_quo q;
	char *value;

	i = 0;
	q = init_quotes_struct();
	value = NULL;
	while((*str)[i])
	{
		manage_struct_quotes(&q, *str, i);
		if (!(q.single_quote) && is_unescapted_c(&q, *str, i, '$'))
		{
			if (next_char_is_question_mark(*str, i))
				manage_question_mark(str, &i, sh->exit_v, sh);
			else if (replace_var_condition(&q, *str, i))
			{
				if ((value = varname_is_in_env((*str) + i + 1, sh)))
					replace_var_by_value(str, &i, value, sh);
				else
					replace_var_by_value(str, &i, "", sh);
			}
		}
		i++;
	}
}

void replace_var_sub_by_true_value(char **arr, t_mini *sh)
{
	int i;
	char *v;
	t_quo q;

	i = 0;
	v = NULL;
	while (arr[++i])
	{
		q = init_quotes_struct();
		if (ft_strlen(arr[i]) <= 1)
				continue;
		else
			manage_substitution_in_str(sh, &arr[i]);
	}
}
