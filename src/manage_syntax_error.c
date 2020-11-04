# include "minishell.h"

int is_syntax_error(char *s, t_mini *sh)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == ';' && s[i + 1] && s[i + 1] == ';')
		{
			ft_printf("minishell: syntax error near unexpected token `;;'\n");
			free_str(s);
			sh->last_return = 2;
			return (1);
		}
	}
	return (0);
}
