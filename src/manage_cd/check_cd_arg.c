# include "minishell.h"

/*apres cd, il y a multi destions*/
int has_multi_valid_arg(char **arr)
{
	int i;
	int lens;

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

/*extract the real destions among several destations if there are, ep: cd $V1 $PWD $V2
 V1 et V2 is "", so it does not take compt*/
char *extract_target_path(char **arr)
{
	int i;

	i = 0;
	while (arr[++i])
	{
		if (arr[i] && ft_strcmp(arr[i], ""))
			return (arr[i]);
	}
	return (NULL);
}

int arg_is_empty(char **arr)
{
	int i;

	i = 0;
	while (arr[++i])
	{
		if (ft_strcmp(arr[i], ""))
			return (0);
	}
	return (1);
}
/*if cmd is only CD OR apres cd, all value are equal to "" */
int is_go_home_opt(char **arr, t_mini *sh)
{
//	char	*str;

	(void)sh;
//	str = extract_target_path(arr);
	if (ft_tablen(arr) == 1
		|| arg_is_empty(arr))
		return (1);
	return (0);
}
