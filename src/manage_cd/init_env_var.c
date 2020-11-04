# include "minishell.h"

void init_env_var(t_mini *sh)
{
	char *path;
	char *new_path;
	char *arr[3] = {ENV_OLDPWD, ENV_PWD, NULL};
	int i;

	i = -1;
	path = getcwd(NULL, 0);
	while (++i < 2)
	{
		//if did not find OLDPWD, or PWD in env, then set them
		if (!ft_find_env(arr[i], sh->env))
		{
			new_path = ft_strnew(ft_strlen(arr[i]) + ft_strlen(path) + 1);
			ft_strcat(new_path, arr[i]);
			ft_strcat(new_path, path);
			ft_envadd(new_path, sh);
			free_str(new_path);
		}
	}
	free_str(path);
}
