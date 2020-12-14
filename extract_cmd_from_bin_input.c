/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_from_bin_input.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:41:10 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:41:11 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_bin_directory_index(char *str)
{
	int	lens;
	int	index;

	lens = ft_strlen(str);
	index = lens - 1;
	while (str && str[index] && str[index] != '/')
		index--;
	return (index);
}

static int	is_invalid_bin_path(int index, char *cmd)
{
	return (!index
		|| (cmd[0] == '/' && index == (int)(ft_strlen(cmd) - 1)));
}

char		*extract_cmd_from_bin_cmd(int index, char *bin_cmd)
{
	char	*tmp;

	tmp = ft_strnew(ft_strlen(bin_cmd) - index + 1);
	ft_strncat(tmp, bin_cmd + index + 1, ft_strlen(bin_cmd) - index);
	bin_cmd = tmp;
	return (bin_cmd);
}

int			cmd_is_in_bin_dir(char *bin_dir, char *cmd)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(bin_dir);
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			if (!ft_strcmp(cmd, dir->d_name))
			{
				closedir(d);
				return (1);
			}
			dir = readdir(d);
		}
		closedir(d);
	}
	return (0);
}

/*
** "if (is_invalid_bin_path(index, bin_cmd))" // ex: "/path" OR "/path/sth/"
*/

char		*manage_binary_cmd(char *bin_cmd, t_mini *sh)
{
	char	*bin_dir;
	char	*cmd;
	int		index;
	char	*path;

	index = get_bin_directory_index(bin_cmd);
	path = NULL;
	if (is_invalid_bin_path(index, bin_cmd))
	{
		show_error_message(bin_cmd, BIN_ERROR, sh);
		return (NULL);
	}
	cmd = extract_cmd_from_bin_cmd(index, bin_cmd);
	bin_dir = ft_strnew(index + 1);
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
