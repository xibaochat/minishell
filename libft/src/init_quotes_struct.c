#include "libft.h"

t_quo init_quotes_struct(void)
{
	t_quo	quo;

	quo.have_quote = 0;
	quo.double_quote = 0;
	quo.single_quote = 0;
	return (quo);
}
