#include "libft.h"

static int	str_is_all_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != SINGLE && s[i] != DOUBLE)
			return (0);
	}
	return (1);
}

static void	cmd_is_cd_and_q(char **arr)
{
	int		i;
	char	*tmp;

	i = 1;
	while (arr[i])
	{
		if (str_is_all_quote(arr[i]))
		{
			tmp = arr[i];
			arr[i] = ft_strnew(2);
			arr[i][0] = '.';
			free_str(tmp);
		}
		i++;
	}
}

static int	cmd_is_echo_and_q(char **arr)
{
	int		i;

	i = 1;
	while (arr[i])
	{
		if (str_is_all_quote(arr[i]))
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
		if (str_is_all_quote(arr[i]))
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
	int		i;

	i = -1;
	if (!arr)
		return ;
	if (!ft_strcmp(arr[0], "cd"))
		cmd_is_cd_and_q(arr);
	else
	{
		if (!ft_strcmp(arr[0], "echo")
			&& cmd_is_echo_and_q(arr) && !has_sub)
			change_q_by_space(arr);
		while (arr[++i])
		{
			//			if (!has_sub)
//			  export TEST='bonjour'] echo "|$TEST|"*/
				delete_quotes_from_s(&arr[i]);
		}
	}
}
