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

void    change_dir_for_other_opts(t_mini *sh, char *path, char *old_p)
{
	char *curr_path;

    if (chdir(path) == -1)
        cd_error_message(path);
    else
    {
		curr_path = getcwd(NULL, 0);
        change_env_var_value(sh->env, old_p, "OLDPWD=");
        change_env_var_value(sh->env, curr_path, "PWD=");
    }
}
