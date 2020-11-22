#include "libft.h"

static int	str_is_all_single_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '\'')
			return (0);
	}
	return (1);
}

static void	cmd_is_cd_and_single_q(char **arr)
{
	int		i;
	char	*tmp;

	i = 1;
	while (arr[i])
	{
		if (str_is_all_single_quote(arr[i]))
		{
			tmp = arr[i];
			arr[i] = ft_strnew(2);
			arr[i][0] = '.';
			free_str(tmp);
		}
		i++;
	}
}

void	delete_quotes_from_arr(char **arr)
{
	int		i;

	i = -1;
	if (!arr)
		return ;
	if (!ft_strcmp(arr[0], "cd"))
		cmd_is_cd_and_single_q(arr);
	else
	{
		while (arr[++i])
			delete_quotes_from_s(&arr[i]);
	}
}
