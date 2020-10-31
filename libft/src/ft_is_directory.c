# include "libft.h"

int			ft_get_directory(char *execname, char *directory)
{
	int		dir_descriptor;

	dir_descriptor = open(directory, O_DIRECTORY);
	if (dir_descriptor > 0)
	{
		close(dir_descriptor);
		ft_putstr_fd(execname, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(directory, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	return (0);
}
