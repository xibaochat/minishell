#include "minishell.h"

int	get_varname_len(const char *s, int i)
{
	int		len;
	t_quo	q;

	len = 0;
	q = init_quotes_struct();
	while (s[++i])
	{
		manage_struct_quotes(&q, s, i);
		if (!((ft_isalnum(s[i]) || s[i] == '_')))
			break ;
		++len;
	}
	return (len);
}

/*in the situation var should be replaced*/

int	replace_var_condition(t_quo *q, char *s, int i)
{
	if (s[i + 1])
	{
		if (q->double_quote && !get_varname_len(s, i))
			return (0);
		return (1);
	}
	return (0);
}

static void	replace_sub_by_true_value(char **str, int *i, t_mini *sh)
{
	char	*value;

	value = varname_is_in_env((*str) + *i + 1, sh);
	if (value)
		replace_var_by_value(str, i, value, sh);
	else
		replace_var_by_value(str, i, "", sh);
	sh->has_sub = 1;
}

/*replace value after $, 1.$? 2. if $VAR exists, replace by value in ENV
 **3. $INVALID_VAR , replace ""
 */

void	manage_substitution_in_str(t_mini *sh, char **str)
{
	int		i;
	t_quo	q;

	i = 0;
	q = init_quotes_struct();
	while ((*str)[i])
	{
		manage_struct_quotes(&q, *str, i);
		if (!(q.single_quote) && is_unescapted_c(&q, *str, i, '$'))
		{
			if (next_char_is_question_mark(*str, i))
				manage_question_mark(str, &i, sh->exit_v);
			else if (is_unescapted_c(&q, *str, i + 1, '/')
					 || is_unescapted_c(&q, *str, i + 1, '='))
				i++;
			else if ((*str)[i + 1] && ft_isdigit((*str)[i + 1]))
				ft_strlcpy(*str + i, *str + i + 2, ft_strlen(*str + i + 2) + 1);
			else if (replace_var_condition(&q, *str, i))
				replace_sub_by_true_value(str, &i, sh);
			else
				i++;
		}
		else
			i++;
	}
}

/*replace chaque str in arr*/

void	replace_var_sub_by_true_value(char **arr, t_mini *sh)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (ft_strlen(arr[i]) <= 1)
			continue ;
		else
			manage_substitution_in_str(sh, &arr[i]);
	}
}
