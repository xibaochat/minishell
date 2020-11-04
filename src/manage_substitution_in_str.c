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
		if (s[i] &&
			(is_unescapted_c(&q, s, i, '$')
			 || is_unescapted_c(&q, s, i, '?')
			 || is_unescapted_c(&q, s, i, '\\')
			 || is_unescapted_c(&q, s, i, SINGLE)
			 || is_unescapted_c(&q, s, i, DOUBLE)))
			break;
		++len;
	}
	ft_printf("lens is %d\n", len);
	return (len);
}

char *extract_str_wo_quote(char *s)
{
	char *new;
	int len;

	len = get_varname_len(s, -1);
	new = ft_strnew(len + 1);
	return (ft_strncat(new, s, len));
}
char *varname_is_in_env(char *s, t_mini *sh)
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

void replace_var_by_value(char **s, int *i, char *v, t_mini *sh)
{
    char *str;
    int varname_len;

    varname_len = get_varname_len(*s, *i);
    str = ft_strnew(ft_strlen(*s) - varname_len + ft_strlen(v));
    ft_strncat(str, *s, *i);
    ft_strncat(str, v, ft_strlen(v));
    if ((*s)[*i + varname_len + 1] != '\0')
        ft_strncat(str, *s + *i + varname_len + 1, ft_strlen(*s) - *i - varname_len);
    free_str(*s);
    *s = str;
    *i += (*i) + ft_strlen(v);
}
