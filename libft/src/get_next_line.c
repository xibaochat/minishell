/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 19:10:21 by xinwang           #+#    #+#             */
/*   Updated: 2020/10/01 00:40:11 by maobe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"



static int			no_newline_in_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (0);
	return (1);
}

static int			get_content_from_file(int fd, char **buffer)
{
	int		nb_read;
	char	*s;
	char	*buff;

	if (!(buff = ft_strnew(BUFFER_SIZE + 1)))
		return (-1);
	nb_read = read(fd, buff, BUFFER_SIZE);
	if (!nb_read && !ft_strlen(*buffer))
	{
		free_str(buff);
		return (nb_read);
	}
	else if (!nb_read)
	{
		free_str(buff);
		return (get_content_from_file(fd, buffer));
	}
	buff[nb_read] = '\0';
	if (!(s = ft_strnew(ft_strlen(*buffer) + nb_read + 1)))
		return (-1);
	if (*buffer)
	{
		s = ft_strncat(s, *buffer, ft_strlen(*buffer));
		free_str(*buffer);
	}
	*buffer = ft_strncat(s, buff, nb_read);
	free_str(buff);
	if (no_newline_in_str(*buffer))
		return (get_content_from_file(fd, buffer));
	return (1);
}

static int			extract_line(char **line, char **buffer, int *i, int *j)
{
	char	*s;
	char	*s1;
	char	*tmp;

	while ((*buffer)[*i] && (*buffer)[*i] != '\n')
		(*i)++;
	if (!(s = ft_strnew(*i + 1)))
		return (-1);
	*line = ft_strncat(s, *buffer, *i);
	*j = ft_strlen(*buffer) - *i;
	if (!*j)
		return (0);
	if ((s1 = ft_strnew(*j)))
	{
		tmp = ft_strncat(s1, *buffer + *i + 1, *j - 1);
		free_str(*buffer);
		*buffer = tmp;
		return (1);
	}
	return (-1);
}

static int			manage_buffer(char **buffer, char **line)
{
	int res;
	int	i;
	int	j;

	i = 0;
	j = 0;
	res = 0;
	if ((res = extract_line(line, buffer, &i, &j) != 1))
	{
		if (res == -1)
			return (nigun_static(buffer, -1));
		return (nigun_static(buffer, 0));
	}
	return (1);
}

int					get_next_line(int fd, char **line)
{
	char **buffer;

	buffer = get_buffer();
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
	{
		if (*buffer)
			free_str(*buffer);
		return (-1);
	}
	if (no_newline_in_str(*buffer))
	{
		if (get_content_from_file(fd, buffer) == -1)
			return (nigun_static(buffer, -1));
		if (!(*buffer))
		{
			*line = ft_strnew(1);
			return (0);
		}
	}
	return (manage_buffer(buffer, line));
}
