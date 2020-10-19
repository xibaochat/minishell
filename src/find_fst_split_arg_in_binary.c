# include <dirent.h>
# include <stdio.h>
# include "minishell.h"

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

static int extract_cmd(char *str)
{
	char *new_cmd;
	int lens;
	int i;
	int index;

	i = 0;
	lens = ft_strlen(str);
	index = lens - 1;
	while (str && str[index] != '/')
		index--;
	return index;
}

//cmd : /bin/ls or /meishaonv/ls
char **get_arr_based_on_extracted_cmd(char *str)
{
	char *s;
	char **arr;
	int i;

	i = extract_cmd(str);
	s = ft_strnew(i + 1);
	s = ft_memcpy(s, str, i);
	arr = (char **)malloc(sizeof(char *) * 2);
	arr[0] = s;
	arr[1] = NULL;
	return (arr);
}

static int is_path_before_cmd(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '/')
			return (1);
	}
	return (0);
}

char *find_full_binary_path(char *cmd, t_mini *sh)
{
	DIR           *d;
	struct dirent *dir;
	char **bin_path;
	int i;
	char *full_path;

	i = -1;
	if (is_path_before_cmd(cmd)) //ex: /bin/ls, cmd is ls, bin_path is /bin/
	{
		bin_path = get_arr_based_on_extracted_cmd(cmd);
		cmd = cmd + extract_cmd(cmd) + 1;
	}
	else
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
