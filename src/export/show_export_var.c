#include "minishell.h"

int ft_putstr_until(char *s, char c, int fd)
{
    int i;

    i = 0;
    while (s[i] != c && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
    return (i);
}

void display_env_w_prefix(char **av, char **env, int fd)
{
	int i;
	char *ptr;

	i = 0;
	if (ft_tablen(av) == 1)
    {
        i = 0;
        while (env[i])
        {
            ft_putstr_fd("declare -x ", fd);
            ft_putstr_until(env[i], '=', fd);
            ft_putstr_fd("=\"", fd);
            ptr = ft_strchr(env[i++], '=');
            if (ptr)
                ft_putstr_fd(ptr + 1, fd);
			ft_putstr_fd("\"", fd);
			ft_putstr_fd("\n", fd);

        }
    }
}
