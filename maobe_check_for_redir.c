#include <stdio.h>
#include <stdlib.h>
# include "libft.h"
# include "minishell.h"

#define READ 0
#define WRITE 1
#define APPEND 2

typedef struct  t_red
{
    int     red_type;
    char    *filename;
    int     fd;
    int     error;
    char    *error_msg;
    int     p[2];

}               t_red;

int jump_to_redir_char(const char *cmd, int *i);
int get_filename_len(const char *cmd, int i);
int jump_i_to_filename(char *str, int i);



t_red init_red_struct(void)
{
    t_red s;

    s.filename = NULL;
    s.fd = -1;
    s.error = 0;
    s.p[0] = -1;
    s.p[1] = -1;
    return (s);
}

void set_red_type(char *str, int i, t_red *red)
{
	if (str[i] && str[i] == '<')
		red->red_type = READ;
	else if (str[i] && str[i + 1] && str[i +1] == '>')
		red->red_type = APPEND;
	else
		red->red_type = WRITE;
}

int manage_redir_type(char *str, int i, t_red *red)
{
	if (!valid_red_char_combinaison(str, i))
	{
		red->error = 1;
		red->error_msg = ft_strdup("minishell: error invalid redi\
rection\n");
		return (-1);
	}
	else
	{
		set_red_type(str, i, red);
		return (0);
	}
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
	red->filename = filename;
}

int store_fd_from_filename(t_red *red)
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
		red->error = -1;
		red->error_msg = ft_strdup("Permission denied\n");
		return (-1);
	}
	return (0);
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

int manage_redirection(t_red *red)
{
	int val;

	if (red->red_type == READ)
		val = dup2(red->fd, 0);
	else
		val = dup2(red->fd, 1);
	if (val < 0)
	{
		red->error = 1;
		red->error_msg = ft_strdup("DUP2 FAILED\n");
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
		new_str = ft_strnew(2);
		new_str[0] = 2;
	}
//	free_str(*str);
	*str = new_str;
}

int manage_redir(char **str)
{
	t_red red;
	int i;
	int res;

	red =  init_red_struct();
	i = 0;
	if (!valid_red_char_combinaison(*str, i))
	{
		redirection_message_err(*str[i]);
		return (-1);
	}
	if (!is_redir_char((*str)[i]) && !jump_to_redir_char(*str, &i))
        return (-1);
	while (redir_in_str(*str) && extract_red(*str, i, &red))
	{
		res = manage_redirection(&red);
		if (res == -1)
		{
			ft_putstr(red.error_msg);
			free_str(red.error_msg);
			return (-1);
		}
		remove_redir_from_cmd(&red, str, i);
	}
	return (0);

}

char ** merge_redir_str_and_redirection(char **arr, t_mini *sh)
{
	int i;
	int redir_res;

	i = -1;
	redir_res = 0;
	while (arr[++i])
	{
		if (redir_in_str(arr[i]))
		{
			if (lonely_redir_char(arr[i]))
			{
				if (manage_lonely_redir_char(i, &arr) == -1)
					return (NULL);
			}
			redir_res = manage_redir(&arr[i]);
			if (redir_res == -1)
			{
				redirection_message_err(arr[i + 1][0]);
				sh->last_return  = 2;
				return (NULL);
			}
		}
	}
	return (arr);
}

char **maobe_check_for_redir(char **arr, t_mini *sh)
{
	int i;
	char **merge_arr;
	int lens;
	char **new_arr;

	merge_arr = merge_redir_str_and_redirection(arr, sh);
	if (merge_arr)
	{
		lens = 0;
		i = 0;
		new_arr = NULL;
		lens = 0;
		while (merge_arr[i])
		{
			if (merge_arr[i][0] != 2)
				lens++;
			i++;
		}
		i = -1;
		new_arr = (char **) malloc(sizeof(char *) * (lens + 1));
		while (++i <= lens)
			new_arr[i] = NULL;
		i = -1;
		int j = 0;
		while (merge_arr[++i])
		{
			if (merge_arr[i][0] != 2)
				new_arr[j++] = merge_arr[i];
		}
		return(new_arr);
	}
	return (NULL);
}
