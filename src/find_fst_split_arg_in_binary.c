# include "minishell.h"

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

//cmd : /bin/ls or /meishaonv/ls
char **get_bin_directory_path(char *str)
{
	char *s;
	char **arr;
	int i;

	arr = NULL;
	i = get_bin_directory_index(str);
	if (i)//if it is not an directory
	{
		s = ft_strnew(i + 1);
		s = ft_memcpy(s, str, i);
		arr = (char **)malloc(sizeof(char *) * 2);
		arr[0] = s;
		arr[1] = NULL;
	}
	return (arr);
}

int is_binary_path(char *s)
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
	char **bin_path;
	char *full_path;
	char *tmp;

	bin_path = NULL;
	full_path = NULL;
	tmp = cmd;
	//if complete  path is given by user
 	if (is_binary_path(cmd)) //ex: /bin/ls, cmd is ls, bin_path is /bin/
	{
		bin_path = manage_binary_cmd(cmd, sh);
		if (bin_path)
			cmd = extract_cmd_from_bin_cmd(cmd);
		else
			return (NULL);
	}
	else
		bin_path = get_bin_path(sh);
	//check cmd is well inside the binary dossier? and in which ?
	full_path = check_cmd_and_return_full_bin_path(cmd, bin_path);
	if (!full_path)
	{
		show_err_message(cmd, sh, bin_path);
		return (NULL);
	}
	return (full_path);
}
