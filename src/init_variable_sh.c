#include "minishell.h"

t_mini	**get_sh(void)
{
	static t_mini	*sh = NULL;

	return (&sh);
}

void	init_sh(char **env, t_mini **sh)
{
	sh = get_sh();
	(*sh) = (t_mini *)malloc(sizeof(t_mini));
	(*sh)->last_return = 0;
	(*sh)->is_cmd = 0;
	(*sh)->ctrl_c = 0;
	(*sh)->exit_v = 0;
	cpy_env(*sh, env);
	(*sh)->is_pipe = 0;
	(*sh)->newfd = 0;
}
