#	include "libft.h"

char	**empty_arr(void)
{
	char		**res;

	res = (char **)malloc(sizeof(char *));
	res[0] = NULL;
	return (res);
}
