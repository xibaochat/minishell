#include "libft.h"

static int	str_is_all_quote(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static void	cmd_is_cd_and_q(char **arr)
{
	char	*tmp;

	tmp = arr[1];
	arr[1] = ft_strnew(2);
	arr[1][0] = '.';
	free_str(tmp);
}

static int	cmd_is_echo_and_q(char **arr)
{
	int		i;

	i = 1;
	while (arr[i])
	{
		if (str_is_all_quote(arr[i], DOUBLE)
			|| str_is_all_quote(arr[i], SINGLE))
			return (1);
		i++;
	}
	return (0);
}

void	change_q_by_space(char **arr)
{
	int		i;
	char	*tmp;

	i = 1;
	while (arr[i])
	{
		if (str_is_all_quote(arr[i], DOUBLE)
			|| str_is_all_quote(arr[i], SINGLE))
		{
			tmp = arr[i];
			arr[i] = ft_strnew(2);
			arr[i][0] = 3;
			free_str(tmp);
		}
		i++;
	}
}

void	delete_quotes_from_arr(char **arr, int has_sub)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	if (!ft_strcmp(arr[0], "cd"))
	{
		if (ft_tablen(arr) > 2)
			return ;
		else if (ft_tablen(arr) == 2
			&& (str_is_all_quote(arr[1], DOUBLE)
				|| str_is_all_quote(arr[1], SINGLE)))
		{
			cmd_is_cd_and_q(arr);
			return ;
		}
	}
	if (!ft_strcmp(arr[0], "echo") && cmd_is_echo_and_q(arr) && !has_sub)
		change_q_by_space(arr);
	while (arr[++i])
		delete_quotes_from_s(&arr[i]);
}
