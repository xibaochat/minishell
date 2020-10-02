#include "minishell.h"

static void	change_pwd_val_in_env(char **env, char *new_p)
{
	int i;
	char *old_path;
	char *tmp;
	char *s;

	i = -1;
	while (env[++i])
    {
       old_path = ft_strnstr(env[i], "PWD=", ft_strlen(env[i]));
        if (old_path)
            break ;
    }
	tmp = env[i];
	s = ft_strnew(ft_strlen("PWD=") + ft_strlen(new_p) + 1);
	ft_strncat(s, "PWD=", 4);
	ft_strncat(s, new_p, ft_strlen(new_p));
	env[i] = s;
	free(tmp);
}

void		pwd(t_mini *sh)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_putstr_w_new_line(strerror(errno));
	else
	{
		change_pwd_val_in_env(sh->env, path);
		ft_putstr_w_new_line(path);
		free(path);
	}
}
