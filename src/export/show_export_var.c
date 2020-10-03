#include "minishell.h"

int ft_putstr_until(char *s, char c)
{
    int i;

    i = 0;
    while (s[i] != c && s[i])
        ft_putchar(s[i++]);
    return (i);
}

void display_env_w_prefix(char **av, char **env)
{
	int i;
	char *ptr;

	i = 0;
	if (ft_tablen(av) == 1)
    {
        i = 0;
        while (env[i])
        {
            ft_putstr("declare -x ");
            ft_putstr_until(env[i], '=');
            ft_putstr("=\"");
            ptr = ft_strchr(env[i++], '=');
            if (ptr)
                ft_putstr(ptr + 1);
            ft_putendl("\"");
        }
    }
}
