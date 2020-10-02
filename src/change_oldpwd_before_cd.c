#include "minishell.h"

void change_oldpwd(t_mini *sh)
{
	char	*path;

	path = getcwd(NULL, 0);
	change_env_var_value(sh->env, path, "OLDPWD=");
}
