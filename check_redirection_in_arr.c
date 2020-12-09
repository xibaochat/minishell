#include "minishell.h"

int	valid_red_char_combinaison(char *cmd, int i)
{
	if (!cmd[i])
		return (0);
	else if (has_pluseur_red_char(cmd, i)
		|| has_mix_red_char(cmd, i) || has_only_red_char(cmd, i))
		return (0);
	return (1);
}

void	redirection_message_err(char c)
{
	ft_putstr("minishell: syntax error near unexpected token `");
	write(1, &c, 1);
	ft_putstr("\n");
}

void	redirection_message_err_2(void)
{
	ft_putstr("minishell: syntax error near unexpected token `newline\n");
}

int	is_redir_char(const char c)
{
	return (c == '>' || c == '<');
}

int	redir_in_str(const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (is_redir_char(s[i]))
			return (1);
	return (0);
}
