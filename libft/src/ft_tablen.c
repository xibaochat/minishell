# include "libft.h"

size_t      ft_tablen(char **tab)
{
    int     len;

    len = 0;
    if (tab)
    {
        while (tab[len])
            len++;
    }
    return (len);
}
