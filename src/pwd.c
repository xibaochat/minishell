#include "minishell.h"

void		pwd(t_mini *sh)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_putstr_w_new_line(strerror(errno));
	else
	{
		ft_putstr_w_new_line(path);
		free_str(path);
	}
}
