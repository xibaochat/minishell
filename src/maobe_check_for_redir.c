#include <stdio.h>
#include <stdlib.h>
# include "libft.h"

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
int redirection_message_err(void);
int merge_str_and_create_new_arr(char ***arr, int i);
int valid_red_char_combinaison(char *cmd, int i);
int get_filename_len(const char *cmd, int i);
int jump_i_to_filename(char *str, int i);
int is_redir_char(const char c);
int redir_in_str(const char *s);

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

int lonely_redir_char(char *str)
{
	if ((str[0] == '>' || str[0] == '<') && ft_strlen(str) == 1)
		return (1);
	else if (str[0] && str[1] &&
			 str[0] == '>' && str[1] == '>' && ft_strlen(str) == 2)
		return (1);
	return (0);
}

void    ft_tabfree(char **tab)
{
    int i;

    i = -1;
    if (tab)
    {
        while (tab[++i])
            free_str(tab[i]);
        free(tab);
        tab = NULL;
    }
}

void    show_arr_value(char **arr)
{
    int i;

    i = -1;
    if (arr)
    {
        while (arr[++i])
            ft_putstr_w_new_line(arr[i]);
    }
}

int  tablen(char **tab)
{
    int len;

    len = 0;
    while (tab[len] != NULL)
        len++;
    return (len);
}

void merge_two_args(char ***arr, int index)
{
	char **new_arr;
	int i;
	int tmp_index;
	size_t lens;

	i = -1;
	tmp_index = index;
	lens = tablen(*arr);
	new_arr = NULL;
	new_arr = (char **)malloc(sizeof(char *) * (lens));
	while (++i < lens)
		new_arr[i] = NULL;
	i = -1;
	while (++i <= index)
		new_arr[i] = ft_strdup((*arr)[i]);
	index += 2;
	while ((*arr)[index])
	{
		new_arr[i] = ft_strdup((*arr)[index]);
		index++;
		i++;
	}
	*arr = new_arr;
}

int merge_str_and_create_new_arr(char ***arr, int i)
{
	char *tmp;

	tmp  = NULL;
	tmp = ft_strjoin((*arr)[i] , (*arr)[i + 1]);
	if (valid_red_char_combinaison(tmp, 0))
	{
		free_str((*arr)[i]);
		(*arr)[i] = tmp;
		merge_two_args(arr, i);
		return (1);
	}
	else
	{
		free_str(tmp);
		return (-1);
	}
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
//	ft_printf("fd is %d\n", red->fd);
	if (red->fd == -1)
	{
		ft_printf("YESYES");
		ft_printf("filename is %s red->red_type is %d\n", f, red->red_type);
		red->error = -1;
		red->error_msg = ft_strdup("Invalid file: \n");
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

int manage_redirection(t_red *red, int i)
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

char *remove_redir_from_cmd(t_red *red, char *str, int i)
{
	int removed_lens;
	int	total_lens;
	char *new_str;

	total_lens = ft_strlen(str);
	new_str = NULL;
	if (red->red_type == READ || red->red_type == WRITE)
		removed_lens = 1 + ft_strlen(red->filename);
	else
		removed_lens = 2 + ft_strlen(red->filename);
	new_str = ft_strnew(total_lens - removed_lens + 1);
	ft_strncat(new_str, str, i);
	ft_strncat(new_str, str + i + removed_lens, total_lens - removed_lens);
	if (!new_str[0])
	{
		new_str = ft_strnew(2);
		new_str[0] = 3;
	}

	//free_str(str);
	return (new_str);
}

int manage_redir(char *str)
{
	t_red red;
	int i;
	int res;

	red =  init_red_struct();
	i = 0;
//	ft_putstr("before0\n");
	if (!is_redir_char(str[i]) && !jump_to_redir_char(str, &i))
        return (-1);
//	ft_putstr("before\n");
	while (redir_in_str(str) && extract_red(str, i, &red))
	{
//		ft_putstr("after\n");
//		ft_printf("_%s_\n", red.filename);
		res = manage_redirection(&red, i);
		if (res == -1)
		{
			ft_putstr(red.error_msg);
			free_str(red.error_msg);
			return (-1);
		}
		ft_putstr("miaomiao\n");
		str = remove_redir_from_cmd(&red, str, i);
//		if (!jump_to_redir_char(str, &i))
//			return (0);
	}
	if (red.error)
	{
		ft_putstr(red.error_msg);
		free_str(red.error_msg);
		return (-1);
	}
	return (0);

}

//int main(void)
char **maobe_check_for_redir(char **arr, t_mini *sh)
{
	int i;
	char *tmp;

	tmp  = NULL;
	i = -1;
	int res;
//	char *s = "echo jojo > lulu > dodo";
//	char **arr = ft_split_w_quotes(s, ' ');
	while (arr[++i])
	{
		ft_putstr(ft_itoa(i));
		if (redir_in_str(arr[i]))
		{
			if (lonely_redir_char(arr[i]))
			{
				if (arr[i + 1])
				{
					res = merge_str_and_create_new_arr(&arr, i);
					if (res == -1)
					{
						ft_tabfree(arr);
						redirection_message_err();
						return (-1);
					}
					else
						manage_redir(arr[i]);
				}
				else
				{
					ft_tabfree(arr);
					redirection_message_err();
					return (-1);
				}
			}
			else
				manage_redir(arr[i]);
		}
	}
	ft_tabfree(arr);
}

/* int main(void) */
/* { */
/* 	char *arr[21] = { */
/* 		// VALID */
/* 		">boid", */
/* 		">>boid", */
/* 		">file0>file1", */
/* 		">file0>file1<fil2", */
/* 		">file0>>", */
/* 		">file0>", */

/* 		// INVALID */
/* 		">>", */
/* 		">", */
/* 		"<", */
/* 		"><", */
/* 		">><", */
/* 		"<<", */
/* 		"<<<", */
/* 		">>>>>>>>>>>>>>>>>>>>>", */
/* 		">>>>", */
/* 		">>>", */
/* 		"> >", */
/* 		"> > >", */
/* 		">> >", */
/* 		"< >", */
/* 		"< <" */
/* 	}; */
/* 	int i = -1; */
/* 	int res = 0; */

/* 	while (++i < 21) */
/* 	{ */
/* 		res = valid_red_char_combinaison(arr[i], 0); */
/* 		if (!res) */
/* 			printf("INVALID: _%s_\n", arr[i]); */
/* 	} */
/* } */
