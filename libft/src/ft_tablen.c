# include "libft.h"

size_t      ft_tablen(char **tab)
{
    int     len;

    len = 0;
    while (tab[len] != NULL)
        len += 1;
    return (len);
}
