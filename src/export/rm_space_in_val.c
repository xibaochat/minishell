#include "minishell.h"

int	get_val_lens_wo_quote(char *s)
{
	int	lens;
	int	i;
	t_quo	q;

	q = init_quotes_struct();
	i = 0;
	lens = 0;
	while (s[i])
	{
		manage_struct_quotes(&q, s, i);
		if ((is_unescapted_c(&q, s, i, ' ')
			&& q.have_quote)
			|| s[i] != ' ')
			lens++;
		i++;
	}
	return (lens);
}

void	copy_val_wo_space(char *new, char *s)
{
	int		i;
	int		j;
	t_quo	q;

	i = -1;
	j = -1;
	q = init_quotes_struct();
	while (s[++i])
	{
		manage_struct_quotes(&q, s, i);
		if ((is_unescapted_c(&q, s, i, ' ')
			 && q.have_quote)
			|| s[i] != ' ')
			new[++j] = s[i];
	}
}

void	rmv_space_in_val(char **s)
{
	int		lens;
	char	*new;

	lens = get_val_lens_wo_quote(*s);
	new = ft_strnew(lens + 1);
	copy_val_wo_space(new, *s);
	free_str(*s);
	*s = new;
}
