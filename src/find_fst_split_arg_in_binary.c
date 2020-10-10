#include <dirent.h>
#include <stdio.h>
#include "minishell.h"

static char *get_full_binary_path(char *cmd, char *bin_path)
{
	char *full_path;
	char *tmp;

	tmp = ft_strjoin(bin_path, "/");
	full_path = ft_strjoin(tmp, cmd);
	free_str(tmp);
	return (full_path);
}

static char **get_bin_path(t_mini *sh)
{
	char *path;
	char ** bin_path;

	path = ft_find_env("PATH", sh->env);
	if (!path)
		path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	sh->path = path;
	bin_path = ft_split(path, ':');
	return (bin_path);
}

char *find_full_binary_path(char *cmd, t_mini *sh)
{
	DIR           *d;
	struct dirent *dir;
	char **bin_path;
	int i;
	char *full_path;

	i = -1;
	bin_path = get_bin_path(sh);
	while (bin_path[++i])
	{
		d = opendir(bin_path[i]);
		if (d)
		{
			while ((dir = readdir(d)))
			{
				if (!ft_strcmp(cmd, dir->d_name))
				{
					closedir(d);
					return (get_full_binary_path(cmd, bin_path[i]));
				}
			}
			closedir(d);
		}
	}
	return (NULL);
}
