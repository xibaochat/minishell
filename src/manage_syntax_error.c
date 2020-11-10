# include "minishell.h"

static int line_has_multi_sep(char *s, int i, char c, t_quo *q)
{
	if(s[i] && s[i + 1]
	   && is_unescapted_c(q, s, i, c)
	   && is_unescapted_c(q, s, i + 1, c)
	   && !q->have_quote)
	{
		ft_printf("syntax error near unexpected token `%c%c'\n", c, c);
		return (1);
	}
	return (0);
}

int is_syntax_error(char *s, t_mini *sh)
{
	int i;
	t_quo quo;

	quo = init_quotes_struct();
	i = -1;
	while (s[++i])
	{
		manage_struct_quotes(&quo, s, i);
		if (line_has_multi_sep(s, i, ';', &quo)
			|| line_has_multi_sep(s, i, '|',  &quo))
		{
			free_str(s);
			sh->last_return = 2;
			return (1);
		}
	}
	return (0);
}
