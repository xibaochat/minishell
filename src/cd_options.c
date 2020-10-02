#include "minishell.h"

int cd_to_home_opt(char **arr)
{
	return ((arr[1] && !ft_strcmp(arr[1], "~"))
			|| ft_tablen(arr) == 1);
}

int cd_to_current_dir_opt(char **arr)
{
	return (arr[1] &&
			(!ft_strcmp(arr[1], ".")
			 || !ft_strcmp(arr[1], "~+")));
}

int cd_to_pre_dir_opt(char **arr)
{
	return (arr[1] &&
			(!ft_strcmp(arr[1], "-") ||
			 !ft_strcmp(arr[1],  "~-")));
}
