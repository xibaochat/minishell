#	include "minishell.h"

void	split_fst_arg(char **split_input)
{
	char	**new_arr;

	new_arr = NULL;
	new_arr = ft_split_w_quotes(split_input[0], ' ');
	ft_tabfree(split_input);
	split_input = new_arr;
}
