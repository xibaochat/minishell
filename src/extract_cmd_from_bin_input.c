# include "minishell.h"

int get_bin_directory_index(char *str)
{
	char *new_cmd;
	int lens;
	int i;
	int index;

	i = 0;
	lens = ft_strlen(str);
	index = lens - 1;
	while (str && str[index] && str[index] != '/')
		index--;
	return index;
}

static int is_invalid_bin_path(int index, char *cmd)
{
	return (!index ||
			(cmd[0] == '/' && index == (ft_strlen(cmd) - 1)));
}

char *extract_cmd_from_bin_cmd(int index, char *bin_cmd)
{
	char *tmp;

	tmp = ft_strnew(ft_strlen(bin_cmd) - index + 1);
	ft_strncat(tmp, bin_cmd + index + 1, ft_strlen(bin_cmd) - index);
	bin_cmd = tmp;
	return (bin_cmd);
}

static int cmd_is_in_bin_dir(char *bin_dir, char *cmd)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(bin_dir);
	if (d)
	{
		while ((dir = readdir(d)))
		{
			if(!ft_strcmp(cmd, dir->d_name))
			{
				closedir(d);
				return (1);
			}
		}
		closedir(d);
	}
	return (0);
}

char *manage_binary_cmd(char *bin_cmd, t_mini *sh)
{

	char *bin_dir;
	char *cmd;
	int index;
	char *path;

	index = get_bin_directory_index(bin_cmd);
	path = NULL;
	if (is_invalid_bin_path(index, bin_cmd)) // ex: /path OR /path/sth/
	{
		show_error_message(bin_cmd, BIN_ERROR, sh);
		return (NULL);
	}
	cmd = extract_cmd_from_bin_cmd(index, bin_cmd);
	bin_dir = ft_strnew(index);
	ft_strncat(bin_dir, bin_cmd, index);
	if (cmd_is_in_bin_dir(bin_dir, cmd))
	{
		path = ft_strnew(ft_strlen(bin_cmd) + 1);
		ft_strncat(path, bin_cmd, ft_strlen(bin_cmd));
	}
	else
		show_error_message(bin_cmd, BIN_ERROR, sh);
	free_str(cmd);
	free_str(bin_dir);
	return (path);
}
