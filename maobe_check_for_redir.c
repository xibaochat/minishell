# include "minishell.h"

char **merge_redir_str_and_redirection(char **arr, t_mini *sh)
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
				if (manage_lonely_redir_char(i, &arr, sh) == -1)
					return (NULL);
			}
			redir_res = manage_redir_in_str(&arr[i], sh);
			if (redir_res == -1)
				return (NULL);
			else
				sh->has_redir = 1;
		}
	}
	return (arr);
}

static int	get_merge_tab_lens(char **arr)
{
	int	lens;
	int	i;

	lens = 0;
	i = 0;
	while (arr[i])
	{
		if (arr[i][0] != 2)
			lens++;
		i++;
	}
	return (lens);
}

char **maobe_check_for_redir(char **arr, t_mini *sh)
{
	int 	i;
	int 	j;
	char 	**merge_arr;
	int		lens;
	char	**new_arr;

	merge_arr = merge_redir_str_and_redirection(arr, sh);
	new_arr = NULL;
	j = 0;
	if (merge_arr)
	{
		if (sh->has_redir)
		{
			lens = get_merge_tab_lens(merge_arr);
			i = -1;
			new_arr = (char **) malloc(sizeof(char *) * (lens + 1));
			while (++i <= lens)
				new_arr[i] = NULL;
			i = -1;
			while (merge_arr[++i])
			{
				if (merge_arr[i][0] != 2)
					new_arr[j++] = merge_arr[i];
				else
					free_str(merge_arr[i]);
			}
			return(new_arr);
		}
		else
			return (merge_arr);
	}
	return (NULL);
}
