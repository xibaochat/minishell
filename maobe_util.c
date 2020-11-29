#include <stdio.h>
#include <stdlib.h>
# include "libft.h"
void merge_two_args(char ***arr, int index);
int valid_red_char_combinaison(char *cmd, int i);
int is_redir_char(const char c);

int is_white_space(const char c)
{
    return (c == ' ' || c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' ||c == '\r');
}

int maobe_has_space(char *cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int has_pluseur_red_char(char *cmd, int i)
{
	if (cmd[i] && cmd[i + 1] && cmd[i + 2] && cmd[i] == '>' && cmd[i + 1] == '>'
		&& (cmd[i + 2] == '>' || cmd[i + 2] == '<'))
		return (1);
	else if (cmd[i] && cmd[i + 1] && cmd[i + 2] && cmd[i] == '<' && cmd[i + 1] == '<'
			 && (cmd[i + 2] == '<' || cmd[i + 2] == '>'))
		return (1);
	else if (cmd[i] && cmd[i + 1] && cmd[i] == '<' && cmd[i + 1] == '<')
		return (1);
	return (0);
}

int has_mix_red_char(char *cmd, int i)
{
	if (cmd[i] && cmd[i + 1] && cmd[i] == '>' && cmd[i + 1] == '<')
		return (1);
	else if (cmd[i] && cmd[i + 1] && cmd[i] == '<' && cmd[i + 1] == '>')
		return (1);
	return (0);
}

int has_only_red_char(char *cmd, int i)
{
	if (cmd[i]  && cmd[i + 1] && cmd[i] == '>' && cmd[i + 1] == '>' && !cmd[i + 2])
		return (1);
	if (cmd[i]  && !cmd[i + 1] && (cmd[i] == '>' || cmd[i] == '<'))
		return (1);
	else
		return (0);
}

int jump_i_to_filename(char *str, int i)
{
	while (str[i] && is_redir_char(str[i]))
		++(i);
	while (str[i] && is_white_space(str[i]))
        ++(i);
	return (i);
}

int get_filename_len(const char *cmd, int i)
{
    int len;

    len = 0;
	while (cmd[i] && is_redir_char(cmd[i]))
		i++;
    while (cmd[i] && !is_white_space(cmd[i])
		   && !is_redir_char(cmd[i]))
    {
     	++len;
		i++;
    }
    return (len);
}



int jump_to_redir_char(const char *cmd, int *i)
{
	while (cmd[*i] && (is_redir_char(cmd[*i])))
		(*i)++;
    while (cmd[*i] && !(is_redir_char(cmd[*i])))
		++(*i);
    if (!cmd[*i])
        return (0);
    return (1);
}

int valid_red_char_combinaison(char *cmd, int i)
{
	if (!cmd[i])
		return (0);
	else if (maobe_has_space(cmd, i) || has_pluseur_red_char(cmd, i)
			 || has_mix_red_char(cmd, i) || has_only_red_char(cmd, i)
			 || (cmd[i + 1] && cmd[i + 1] == '|'))
		return (0);
	return (1);
}

void redirection_message_err(char c)
{
	ft_putstr("bash: syntax error near unexpected token `");
	write(1, &c, 1);
	ft_putstr("\n");
}

void redirection_message_err_2()
{
	ft_putstr("bash: syntax error near unexpected token `newline\n");
}

int is_redir_char(const char c)
{
	return (c == '>' || c == '<');
}

int redir_in_str(const char *s)
{
    int i;

    i = -1;
    while (s[++i])
        if (is_redir_char(s[i]))
            return (1);
    return (0);
}
