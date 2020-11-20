#	include "minishell.h"

int	has_multi_valid_arg(char **arr)
{
	int	i;
	int	lens;

	i = 1;
	lens = 0;
	while (arr[i])
	{
		if (arr[i] && ft_strcmp(arr[i], ""))
			lens++;
		i++;
	}
	return (lens);
}

char	*extract_target_path(char **arr)
{
	int	i;

	i = 0;
	while (arr[++i])
	{
		if (arr[i] && ft_strcmp(arr[i], ""))
			return (arr[i]);
	}
	return (NULL);
}

int	arg_is_empty(char **arr)
{
	int	i;

	i = 0;
	while (arr[++i])
	{
		if (ft_strcmp(arr[i], ""))
			return (0);
	}
	return (1);
}

int	is_go_home_opt(char **arr, t_mini *sh)
{
	(void)sh;
	if (ft_tablen(arr) == 1
		|| arg_is_empty(arr))
		return (1);
	return (0);
}
