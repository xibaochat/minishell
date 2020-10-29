# include <dirent.h>
# include <stdio.h>
# include "minishell.h"

static char *get_full_binary_path(char *cmd, char *bin_path, char **bin)
{
	char *full_path;
	char *tmp;

	tmp = ft_strjoin(bin_path, "/");
	full_path = ft_strjoin(tmp, cmd);
	free_str(tmp);
 	ft_tabfree(bin);
	return (full_path);
}

static char **get_bin_path(t_mini *sh)
{
	char *path;
	char ** bin_path;

	path = ft_find_env(ENV_PATH, sh->env);
	if (!path)
		path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
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
	char *tmp;
	char *full_path;

	i = -1;
	tmp = NULL;
	bin_path = NULL;
	full_path = NULL;
	//if complete  path is given by user
 	if (is_path_before_cmd(cmd)) //ex: /bin/ls, cmd is ls, bin_path is /bin/
	{
		bin_path = get_arr_based_on_extracted_cmd(cmd);
		//tmp = cmd + extract_cmd(cmd) + 1;
		tmp = ft_strnew(ft_strlen(cmd) - extract_cmd(cmd) +1);
		tmp = ft_strncat(tmp , cmd + extract_cmd(cmd) + 1, ft_strlen(cmd) - extract_cmd(cmd));
		free_str(cmd);
		cmd = tmp;
	}
	else
		bin_path = get_bin_path(sh);
	//check cmd is well insede the binary dossier? and in which ?
	while (bin_path[++i])
	{
		d = opendir(bin_path[i]);
		if (d)
		{
			while ((dir = readdir(d)))
			{
				// if cmd is inside binary dir
				if (!ft_strcmp(cmd, dir->d_name))
				{
					closedir(d);
					return (get_full_binary_path(cmd, bin_path[i], bin_path));
				}
			}
			closedir(d);
		}
	}
	if (bin_path)
		ft_tabfree(bin_path);
	return (NULL);
}
