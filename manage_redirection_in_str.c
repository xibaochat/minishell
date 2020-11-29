#	include "minishell.h"

t_red init_red_struct(void)
{
    t_red s;

    s.filename = NULL;
    s.fd = -1;
    s.error = 0;
    return (s);
}

int jump_i_to_filename(char *str, int i)
{
	while (str[i] && is_redir_char(str[i]))
		++(i);
	while (str[i] && is_white_space(str[i]))
        ++(i);
	return (i);
}

int manage_redir_type(char *str, int i, t_red *red)
{
	if (!valid_red_char_combinaison(str, i))
	{
		red->error = 1;
		redirection_message_err(str[i]);
		return (-1);
	}
	else
	{
		set_red_type(str, i, red);
		return (0);
	}
}

int extract_red(char *str, int i, t_red *red)
{
	if (manage_redir_type(str, i, red) == -1)
		return (0);
	store_red_filename(str, i, red);
	if (store_fd_from_filename(red) == -1)
		return (0);
    return (1);
}

int manage_redir_in_str(char **str)
{
	t_red red;
	int i;
	int res;

	red =  init_red_struct();
	i = 0;
	if (!is_redir_char((*str)[i]) && !jump_to_redir_char(*str, &i))
        return (-1);
	while (redir_in_str(*str) && extract_red(*str, i, &red))
	{
		res = dup_fd_redirection(&red);
		if (res == -1)
			return (-1);
		remove_redir_from_cmd(&red, str, i);
	}
	return (0);

}
