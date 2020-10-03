#include "minishell.h"

int has_space(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (is_space(s[i]))
			return (1);
	}
	return (0);
}

int has_invald_char_in_env_name(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) &&
			str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int has_no_equal_sign(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	invalid_export_var_val(char *s)
{
	if (has_invald_char_in_env_name(s)
		|| has_space(s) || has_no_equal_sign(s))
		return (1);
	else
		return (0);
}
