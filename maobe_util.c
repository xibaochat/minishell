# include "minishell.h"

int is_white_space(const char c)
{
    return (c == ' ' || c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' ||c == '\r');
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
