#	include "minishell.h"

static int before_there_is_no_redir_c(char *s, int i)
{
	while (s[--i])
	 {
		 if (is_redir_char(s[i]))
			 return (0);
	 }
	 return (1);
}

int lonely_redir_char(char *str)
{
	int last_c;

	last_c = ft_strlen(str) - 1;
	if (!last_c && is_redir_char(str[0]))
		return (1);
	if (str[last_c] && str[last_c - 1]
		&& str[last_c] == '>' && str[last_c - 1] == '>'
		&& before_there_is_no_redir_c(str, last_c - 1))
		return (1);
	else if (str[last_c] == '>' && !is_redir_char(str[last_c - 1])
			 && before_there_is_no_redir_c(str, last_c))
		return (1);
	return (0);
}

void merge_two_args(char ***arr, int index)
{
	char **new_arr;
	int i;
	int lens;

	i = -1;
	lens = ft_tablen(*arr);
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
	//ft_tabfree(*arr);
	*arr = new_arr;
}

int merge_str_and_create_new_arr(char ***arr, int i, t_mini *sh)
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
		sh->last_return = 2;
		redirection_message_err((*arr)[i][0]);
		return (-1);
	}
}

int manage_lonely_redir_char(int i, char ***arr, t_mini *sh)
{
	int res;

	res = -1;
	if ((*arr)[i + 1])
	{
		res = merge_str_and_create_new_arr(arr, i, sh);
		if (res == -1)
			return (res);
		return (1);
	}
	else
		redirection_message_err_2();
	return (res);
}
