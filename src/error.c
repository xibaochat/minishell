# include "minishell.h"

void show_key_error_message(int key, char *s)
{
	if (key == EXPORT)
		ft_putstr_fd("export: `", 2);
	if (key == UNSET)
		ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_w_new_line_fd(VAL_ERROR, 2);
	return ;
}


/*
** this function was copied from show_message_error_if_cmd_cant_find.c file
*/

void show_error_message(char *cmd, char *err, t_mini *sh)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_w_new_line_fd(err, 2);
	sh->last_return = 127;
}

int	ft_error(char *str, int errno_value)
{
	ft_putstr_w_new_line_fd(strerror(errno_value), 2);
	(void)str;
	return (0);
}

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
