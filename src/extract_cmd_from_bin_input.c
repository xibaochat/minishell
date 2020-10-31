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
	while (str && str[index] != '/')
		index--;
	return index;
}

void show_bin_error_message(char *cmd, t_mini *sh)
{
	 ft_putstr_fd(cmd, 2);
	 ft_putstr_fd(": No such file or directory\n", 2);
	 sh->last_return = 127;
}

char **get_bin_dir_arr(char *cmd, int i)
{
	char *str;
	char **arr;

	str = ft_strnew(i + 1);
	ft_strncat(str, cmd, i);
	arr = (char **)malloc(sizeof(char *) * 2);
	arr[0] = str;
	arr[1] = NULL;
	return (arr);
}

char **manage_binary_cmd(char *cmd, t_mini *sh)
{
	int index;
	char **bin_dir_arr;

	bin_dir_arr = NULL;
	index = get_bin_directory_index(cmd);
	if (!index)
		show_bin_error_message(cmd, sh);
	else
		bin_dir_arr = get_bin_dir_arr(cmd, index);
	return (bin_dir_arr);
}

char *extract_cmd_from_bin_cmd(char *cmd)
{
	int index;
	char *tmp;

	index = get_bin_directory_index(cmd);
	tmp = ft_strnew(ft_strlen(cmd) - index + 1);
	ft_strncat(tmp, cmd + index + 1, ft_strlen(cmd) - index);
	cmd = tmp;
	return (cmd);
}
