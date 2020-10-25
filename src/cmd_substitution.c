# include "minishell.h"

int get_varname_len(const char *s, int i)
{
	int len;
	t_quo q;

	len = 0;
	q = init_quotes_struct();
	while (s[++i])
	{
		manage_struct_quotes(&q, s, i);
		if (is_unescapted_c(&q, s, i, '$')
			|| is_unescapted_c(&q, s, i, SINGLE)
			|| is_unescapted_c(&q, s, i, DOUBLE))
			break;
		++len;
	}
	return (len);
}
static int get_dollar_index(t_quo *q, char *s, t_mini *sh)
{
	int i;

	i = -1;
	while (s[++i])
		if (is_unescapted_c(q, s, i, '$'))
			return (i);
	return (-1);
}
char *extract_str_wo_quote(char *s)
{
	char *new;
	int len;

	len = get_varname_len(s, -1);
	new = ft_strnew(len + 1);
	return (ft_strncat(new, s, len));
}
char *get_value_from_env(char *s, t_mini *sh)
{
	int i;
	char *str;
	int lens;
	char *value;

	i = 0;
	if (s)
	{
		str = extract_str_wo_quote(s);
		value = ft_find_env(str, sh->env);
		free_str(str);
		if (value)
			return (value);
	}
	return (NULL);
}
void replace_var_by_value(char **s, int i, char *v, t_mini *sh)
{
	char *str;
	int varname_len;

	varname_len = get_varname_len(*s, i);
	str = ft_strnew(ft_strlen(*s) - varname_len + ft_strlen(v) + 1);
	ft_strncat(str, *s, i);
	ft_strncat(str, v, ft_strlen(v));
	if ((*s)[i + varname_len + 1] != '\0') // STILL AN OTHER VAR TO SUBSTITUE AFTER CURRENT ONE
		ft_strncat(str, *s + i + varname_len + 1, ft_strlen(*s) - i - varname_len);
	free_str(*s);
	*s = str;
}

void replace_var_sub_by_true_value(char **arr, t_mini *sh)
{
	int i;
	int j;
	char *v;
	t_quo q;

	i = 0;
	v = NULL;
	while (arr[++i])
	{
		j = 0;
		q = init_quotes_struct();
		if (ft_strlen(arr[i]) <= 1)
		{
			continue;
		}
		else
		{
			while (arr[i][j])
			{
				manage_struct_quotes(&q, arr[i], j);
				if (!(q.single_quote) && is_unescapted_c(&q, arr[i], j, '$'))
				{
					if (v = get_value_from_env(arr[i] + j + 1, sh))
					{
						replace_var_by_value(&arr[i], j, v, sh);
						j += ft_strlen(v);
					}
					else
						replace_var_by_value(&arr[i], j, "", sh);
				}
				else
					++j;
			}
		}
	}
}
