#include "minishell.h"

/*
 ** manage_redir_input() handles "<" situation, ">" and ">>" are directly handled in manage_redir()
 */

int	manage_redir_input(t_mini *sh, char *file)
{
	sh->newfd = open(file, O_RDWR, 0600);
	if (sh->newfd == -1)
	{
		ft_error("CAN'T OPEN FILE", errno);
	}
	if (dup2(sh->newfd, 0) < 0)
	{
		ft_error("DUP2 FAILED", errno);
	}
	close(sh->newfd);
	return (0);
}

/*
 ** manage_redir() will open (or create) the file for the redirection
 */

int	manage_redir(t_mini *sh, char *file, char *elem, int j)
{
	if (elem[j] == '<')
		return (manage_redir_input(sh, file));
	else
	{
		if (elem[j + 1] == '>')
		{
			sh->newfd = open(file, O_CREAT | O_RDWR | O_APPEND, 0600);
			if (sh->newfd == -1)
				ft_error("CAN'T OPEN FILE", errno);
		}
		else
		{
			sh->newfd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0600);
			if (sh->newfd == -1)
				ft_error("CAN'T OPEN FILE", errno);
		}
		if (dup2(sh->newfd, 1) < 0)
			ft_error("DUP2 FAILED", errno);
		close(sh->newfd);
	}
	return (0);
}

char	*file_name(char **arr, int i, int j, char c)
{
	char	*file;
	int	k;

	k = 0;
	if (!arr[i][j + 1] || (arr[i][j + 1] == c && !arr[i][j + 2]))
	{
		if (!arr[i + 1])
			ft_error("NO FILE_NAME", 2);
		while (arr[i + 1][k] && !ft_strchr("<>", arr[i + 1][k]))
			k++;
		file = ft_substr(arr[i + 1], 0, k);
	}
	else
	{
		if (arr[i][j + 1] == c)
			j++;
		while (arr[i][j + 1 + k] && !ft_strchr("<>", arr[i][j + 1 + k]))
			k++;
		file = ft_substr(arr[i], j + 1, k);
	}
	return (file);
}

/*
 ** Note : file_name() can also be used to get the parameter of "<<" even if it is not a file.
 */
/*
char	*file_name(char **arr, int i, int j, char c)
{
	char	*file;

	if (!arr[i][j + 1] || (arr[i][j + 1] == c && !arr[i][j + 2]))
		file = ft_strdup(arr[i + 1]);
	else
	{
		if (arr[i][j + 1] == c)
			file = ft_strdup(arr[i] + j + 2);
		else
			file = ft_strdup(arr[i] + j + 1);
	}
	return (file);
}*/

/*
 ** exec_redir() will get the name of the redirection file and then call manage_redir()
 */

char	**exec_redir(t_mini *sh, char **arr, int i, int j)
{
	sh->file = file_name(arr, i, j, arr[i][j]);
	if (!sh->file)
	{
		ft_error("NO FILE NAME", 8);
		return (NULL);
	}
	if (manage_redir(sh, sh->file, arr[i], j))
		return (NULL);
	free(sh->file);
	sh->file = NULL;
	return (arr);
}

char	**check_for_redir(char **arr, t_mini *sh)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = NULL;
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (ft_strchr("<>", arr[i][j]) && !(j > 0 && arr[i][j - 1] == '\\'))
			{
				if (!exec_redir(sh, arr, i, j))
					return (NULL);
				tmp = new_cmd(arr, i, j);
				ft_tabfree(arr);
				arr = tmp;
				i = 0;
				j = -1;
			}
		}
	}
	return (tmp);
}
