# include "minishell.h"

char *get_full_bin_path(char *bin_path, char *cmd, char **bin)
{
	char *full_path;
	char *tmp;

	tmp = ft_strjoin(bin_path, "/");
	full_path = ft_strjoin(tmp, cmd);
	free_str(tmp);
 	ft_tabfree(bin);
	return (full_path);
}

char *get_full_path(char *cmd, DIR *d, char **bin_path, int i)
{
	struct dirent *dir;
	char *full_path;

	full_path = NULL;
	while ((dir = readdir(d)))
	{
		if(!ft_strcmp(cmd, dir->d_name))
		{
			closedir(d);
			full_path = get_full_bin_path(bin_path[i], cmd, bin_path);
			return (full_path);
		}
	}
	closedir(d);
	return (NULL);
}

char	*check_cmd_and_return_full_bin_path(char *cmd, char **bin_path)
{
	int i;
	DIR	*d;
	char *full_bin_path;

	full_bin_path = NULL;
	i = -1;
	while (bin_path[++i])
	{
		d =  opendir(bin_path[i]);
		if (d)
		{
			full_bin_path = get_full_path(cmd, d, bin_path, i);
			if (full_bin_path)
				return (full_bin_path);
		}
	}
	return (full_bin_path);
}
