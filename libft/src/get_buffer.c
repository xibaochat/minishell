#include "libft.h"

char **get_buffer(void)
{
    static char *buffer = NULL;

    return (&buffer);
}

void ft_print_buffer(void)
{
    char **buf;

    buf = get_buffer();
    ft_printf("%s\n", *buf);
}
