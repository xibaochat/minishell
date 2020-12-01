#include "minishell.h"

int	has_pluseur_red_char(char *cmd, int i)
{
	if (cmd[i] && cmd[i + 1] && cmd[i + 2] && cmd[i] == '>' && cmd[i + 1] == '>'
		&& (cmd[i + 2] == '>' || cmd[i + 2] == '<'))
		return (1);
	else if (cmd[i] && cmd[i + 1] && cmd[i + 2] && cmd[i] == '<'
		&& cmd[i + 1] == '<' && (cmd[i + 2] == '<' || cmd[i + 2] == '>'))
		return (1);
	else if (cmd[i] && cmd[i + 1] && cmd[i] == '<' && cmd[i + 1] == '<')
		return (1);
	return (0);
}

int	has_mix_red_char(char *cmd, int i)
{
	if (cmd[i] && cmd[i + 1] && cmd[i] == '>' && cmd[i + 1] == '<')
		return (1);
	else if (cmd[i] && cmd[i + 1] && cmd[i] == '<' && cmd[i + 1] == '>')
		return (1);
	return (0);
}

int	has_only_red_char(char *cmd, int i)
{
	if (cmd[i] && cmd[i + 1] && cmd[i] == '>'
		&& cmd[i + 1] == '>' && !cmd[i + 2])
		return (1);
	if (cmd[i] && !cmd[i + 1] && (cmd[i] == '>' || cmd[i] == '<'))
		return (1);
	else
		return (0);
}

static int	redirection_syntax_error_return(void)
{
	ft_putstr("minishell: syntax error near unexpected token\n");
	return (1);
}

int	redirection_syntax_error(char *s)
{
	int		i;
	t_quo	quo;

	quo = init_quotes_struct();
	i = 0;
	while (s[i])
	{
		manage_struct_quotes(&quo, s, i);
		if (!valid_red_char_combinaison(s, i) && !quo.have_quote)
			return (redirection_syntax_error_return());
		if (s[i] && s[i + 1] && s[i] == '>' && s[i + 1] == '>')
			i++;
		if ((s[i] == '>' || s[i] == '<') && !quo.have_quote)
		{
			i++;
			while (s[i] && ft_strchr(SPACE, s[i]))
				i++;
			if (!s[i])
				return (redirection_syntax_error_return());
			if (s[i] == ';' || s[i] == '|' || is_redir_char(s[i]))
				return (redirection_syntax_error_return());
		}
		i++;
	}
	return (0);
}
