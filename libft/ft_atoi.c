/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:38:58 by xinwang           #+#    #+#             */
/*   Updated: 2020/04/20 14:21:39 by osshit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static int	get_start_index(char *str)
{
	int		i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	return (i);
}

long	ft_atoi(const char *s)
{
	long		sign;
	long		res;
	long		i;
	char	*str;

	str = (char *)s;
	sign = 1;
	res = 0;
	i = get_start_index(str);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((long)sign * res);
}
