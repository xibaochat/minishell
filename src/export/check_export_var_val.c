#include "minishell.h"

/*check variable is aloha+num or not,
**if it contains other char OR export =value,
it's invalid
 */
int has_invalid_char_in_env_name(char *str)
{
	int i;

	i = 0;
	if (!i && str[i] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) &&
			str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int has_equal_sign(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && i)
			return (1);
		i++;
	}
	return (0);
}
