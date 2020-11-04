# include "minishell.h"

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
