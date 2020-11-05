#include "minishell.h"

/*
** sticked_next_redir() checks if the next redirection is not separated from the first one
** in the original command.
** For example : "echo jojo>lulu>dodo"
*/

int	sticked_next_redir(char *str)
{
	int	i;
	
	i = 0;
	while (!ft_strchr("<>", str[i]) && str[i])
		i++;
	while (ft_strchr("<>", str[i]) && str[i])
		i++;
	while (!ft_strchr("<>", str[i]) && str[i])
		i++;
	if (str[i])
		return (i);
	return (0);
}

/*
 ** new_cmd() returns the copy of the old cmd without the redirection currently handled.
 ** For ex : new_cmd("echo jojo > lulu") = "echo jojo"
 ** For ex2 : new_cmd("echo jojo > lulu > dodo") = "echo jojo > dodo"
 */


char	**new_cmd(char **arr, int i, int j)
{
	int	len;
	char	**new;
	int	k;
	int	sticked;

	len = (int)ft_tablen(arr);
	if ((!arr[i][j + 1] || arr[i][j + 1] == '>' && !arr[i][j + 2]) && arr[i + 1])
		len--;
	if (!j)
		len--;
	if (sticked = sticked_next_redir(arr[i]))
		len++;
	if (!(new = malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	k = -1;
	while (++k < i)
		new[k] = ft_strdup(arr[k]);
	if (j)
		new[k] = ft_substr(arr[i], 0, j);
	if (sticked)
		new[++k] = ft_substr(arr[i], sticked, ft_strlen(arr[i] - sticked));
	if ((!arr[i][j + 1] || arr[i][j + 1] == '>' && !arr[i][j + 2]) && arr[i + 1])
		i += 2;
	else
		i++;
	while (arr[i])
		new[++k] = ft_strdup(arr[i++]);
	new[++k] = NULL;
	k = -1;
	while (new[++k])
		printf("new[%d] = %s\n", k, new[k]);
	return (new);
}

/*
char	**new_cmd(char **arr, int i, int j)
{
	int	len;
	char	**new;
	int	k;

	new = ft_split_inc(arr, "<>");
	k = -1;
	while (new[++k])
	{
		if (new[k][0] && !ft_strchr("<>", new[k][0]))
			i++;
		
	}
}
*/

void	manage_redir(t_mini *sh, char *file, char *elem, int j)
{
	if (elem[j] == '<')
	{
		if ((sh->newfd = open(file, O_RDWR, 0600)) == -1)
			printf("DEBUG FOR < : OPEN FAILED\n");
		if (dup2(sh->newfd, 0) < 0)
			printf("DEBUG FOR < : DUP2 FAILED\n");
		close(sh->newfd);
	}
	else
	{
		if (elem[j + 1] == '>')
		{
			if ((sh->newfd = open(file, O_CREAT | O_RDWR | O_APPEND, 0600)) == -1)
				printf("DEBUG : OPEN FAILED\n");
		}
		else
		{
			if ((sh->newfd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0600)) == -1)
				printf("DEBUG : OPEN FAILED\n");
		}
		if (dup2(sh->newfd, 1) < 0)
			printf("DEBUG : DUP2 FAILED\n");
		close(sh->newfd);
	}
}

/*
 ** Note : file_name() can also be used to get the parameter of "<<" even if it is not a file.
 */

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
}

char	**check_for_redir(char **arr, t_mini *sh)
{
	int	i;
	int	j;
	char	*file;
	char	**tmp;
	int	k;

	tmp = NULL;
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (ft_strchr("<>", arr[i][j]))
			{
				if (!(file = file_name(arr, i, j, arr[i][j])))
					printf("DEBUG : NO FILE NAME\n");
				manage_redir(sh, file, arr[i], j);
				tmp = new_cmd(arr, i, j);
				ft_tabfree(arr);
				free(file);
				arr = tmp;
				j = 0;
				i = 0;
			}
		}
	}
	return (tmp);
}
