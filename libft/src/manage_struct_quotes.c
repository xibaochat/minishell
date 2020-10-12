#include "libft.h"

void manage_struct_quotes(t_quo *quo, char c)
{
	if (c == '"' && !(quo->single_quote))
	{
		if (!(quo->double_quote))
		{
			++(quo->have_quote);
			++(quo->double_quote);
		}
		else
		{
			--(quo->have_quote);
			--(quo->double_quote);
		}
	}
	else if (c == '\'' && !(quo->double_quote))
	{
		if (!(quo->single_quote))
		{
			++(quo->have_quote);
			++(quo->single_quote);
		}
		else
		{
			--(quo->have_quote);
			--(quo->single_quote);
		}
	}

}
