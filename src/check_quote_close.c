#include "minishell.h"

//check quotes are in pair or not
void check_quote_close(char **arr, t_mini *sh)
{
    int i;
	int j;
    t_quo q;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		q = init_quotes_struct();
		while (arr[i][++j])
			manage_struct_quotes(&q, arr[i], j);
		if (q.have_quote)
		{
			sh->last_return = 1;
			ft_putstr_fd("Quote is not closed:", 2);
			ft_putstr_w_new_line_fd(sh->line, 2);
		}
		else
			sh->last_return = 0;
	}
}
