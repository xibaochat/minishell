# include "minishell.h"

void show_key_error_message(int key, char *s)
{
	if (key == EXPORT)
		ft_putstr_fd("export: `", 2);
	if (key == UNSET)
		ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_w_new_line_fd(VAL_ERROR, 2);
    return ;
}
