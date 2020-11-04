#include "libft.h"

/*
manage cas:  echo she"\\\"s" OR echo \\\"she"\\\
echo "\""
 */
static int is_valid_char(char *s, int i, t_quo q)
{
	return ((s[i] == SINGLE && q.double_quote && !is_escapted(&q, s, i))
			|| (s[i] == DOUBLE && q.single_quote && !is_escapted(&q, s, i))
			|| (s[i] != DOUBLE && s[i] != SINGLE)
			|| is_escapted(&q, s, i));
}

static int get_len_wo_quotes(char *s)
{
    int i;
    int len;
    t_quo q;

    i = -1;
    len = 0;
    q = init_quotes_struct();
    if (!s)
        return (0);
    while (s[++i])
    {
     	manage_struct_quotes(&q, s, i);
		if (is_valid_char(s, i, q))
			len++;
	}
    return (len);
}

static void copy_wo_quotes(char *new, char *s)
{
    int i;
    int j;
    t_quo q;

    i = -1;
    j = -1;
    q = init_quotes_struct();
    while (s[++i])
    {
		manage_struct_quotes(&q, s, i);
		 if (is_valid_char(s, i, q))
            new[++j] = s[i];
    }
}

void delete_quotes_from_s(char **s)
{
	int		final_len;
	char	*new;

	final_len = get_len_wo_quotes(*s);
	new = ft_strnew(final_len + 1);
	copy_wo_quotes(new, *s);
	free_str(*s);
	*s = new;
}
