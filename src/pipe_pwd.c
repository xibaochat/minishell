#include "minishell.h"

void		pipe_pwd(int *fd, t_mini *sh)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_putstr_w_new_line(strerror(errno));
	else
	{
		ft_putstr_fd(path, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free_str(path);
	}
}
