#	include "minishell.h"

void set_red_type(char *str, int i, t_red *red)
{
	if (str[i] && str[i] == '<')
		red->red_type = READ;
	else if (str[i] && str[i + 1] && str[i +1] == '>')
		red->red_type = APPEND;
	else
		red->red_type = WRITE;
}

void store_red_filename(char *str, int i, t_red *red)
{
	int name_lens;
	char *filename;

	name_lens = 0;
	filename = NULL;
	i = jump_i_to_filename(str, i);
	name_lens = get_filename_len(str, i);
	filename = ft_strnew(name_lens + 1);
	ft_strncat(filename, str + i, name_lens);
	free_str(red->filename);
	red->filename = filename;
}

int store_fd_from_filename(t_red *red, t_mini *sh)
{
	char *f;

	f = red->filename;
	if (red->red_type == READ)
		red->fd = open(f, O_RDWR, 0644);
	else if (red->red_type == APPEND)
		red->fd = open(f, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (red->red_type == WRITE)
		red->fd = open(f, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (red->fd == -1)
	{
		free_str(f);
		sh->last_return = 1;
		ft_putstr("Permission denied\n");
		return (-1);
	}
	return (0);
}

int dup_fd_redirection(t_red *red)
{
	int val;

	if (red->red_type == READ)
		val = dup2(red->fd, 0);
	else
		val = dup2(red->fd, 1);
	if (val < 0)
	{
		ft_putstr("DUP2 FAILED\n");
		return (-1);
	}
	return (0);
}

void	remove_redir_from_cmd(t_red *red, char **str, int i)
{
	int removed_lens;
	int	total_lens;
	char *new_str;

	total_lens = ft_strlen(*str);
	new_str = NULL;
	if (red->red_type == READ || red->red_type == WRITE)
		removed_lens = 1 + ft_strlen(red->filename);
	else
		removed_lens = 2 + ft_strlen(red->filename);
	new_str = ft_strnew(total_lens - removed_lens + 1);
	ft_strncat(new_str, *str, i);
	ft_strncat(new_str, *str + i + removed_lens, total_lens - removed_lens);
	if (!new_str[0])
	{
		free_str(new_str);
		new_str = ft_strnew(2);
		new_str[0] = 2;
	}
	free_str(*str);
	free_str(red->filename);
	*str = new_str;
}
