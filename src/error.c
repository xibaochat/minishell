#include "minishell.h"

void	show_key_error_message(int key, char *s)
{
	if (key == EXPORT)
		ft_putstr_fd("export: `", STDERR_FILENO);
	if (key == UNSET)
		ft_putstr_fd("unset: `", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_w_new_line_fd(VAL_ERROR, STDERR_FILENO);
	return ;
}

/*
** If can't find cmd : show error message
*/

void	show_error_message(char *cmd, char *err, t_mini *sh)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_w_new_line_fd(err, 2);
	sh->last_return = 127;
}

/*
** ft_error() uses errno (which is automatically set when failure of malloc, dup2, etc.))
*/

int	ft_error(char *str, int errno_value)
{
	ft_putstr_w_new_line_fd(strerror(errno_value), 2);
	//sh->last_return = errno_value;
	exit(EXIT_FAILURE);
	(void)str;
//	(void)sh;
	return (0);
}

static int	line_has_multi_sep(char *s, int i, char c, t_quo *q)
{
	if (s[i] && s[i + 1]
		&& is_unescapted_c(q, s, i, c)
		&& is_unescapted_c(q, s, i + 1, c)
		&& !q->have_quote)
	{
		ft_printf("syntax error near unexpected token `%c%c'\n", c, c);
		return (1);
	}
	return (0);
}

int	is_syntax_error(char *s, t_mini *sh)
{
	int		i;
	t_quo	quo;

	quo = init_quotes_struct();
	i = -1;
	if (sep_in_str_is_invalid(s, ';')
		|| sep_in_str_is_invalid(s, '|'))
	{
		free_str(s);
		sh->last_return = 2;
		return (1);
	}
	while (s[++i])
	{
		manage_struct_quotes(&quo, s, i);
		if (line_has_multi_sep(s, i, ';', &quo)
			|| line_has_multi_sep(s, i, '|', &quo))
		{
			free_str(s);
			sh->last_return = 2;
			return (1);
		}
	}
	return (0);
}
