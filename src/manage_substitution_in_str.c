# include "minishell.h"

/*calculate variable name lenth*/
char *extract_str_wo_quote(char *s)
{
	char *new;
	int len;

	len = get_varname_len(s, -1);
	new = ft_strnew(len + 1);
	return (ft_strncat(new, s, len));
}
/*check var is inside ENV or not,
  if it is, return its value*/
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
/*remplir var value by its variable in arr*/
void replace_var_by_value(char **s, int *i, char *v, t_mini *sh)
{
    char *str;
    int varname_len;

    varname_len = get_varname_len(*s, *i);
    str = ft_strnew(ft_strlen(*s) - varname_len + ft_strlen(v) + 1);
    ft_strncat(str, *s, *i);
    ft_strncat(str, v, ft_strlen(v));
    if ((*s)[*i + varname_len + 1] != '\0')
        ft_strncat(str, *s + *i + varname_len + 1, ft_strlen(*s) - *i - varname_len);
    free_str(*s);
    *s = str;
    *i += ft_strlen(v);
}
