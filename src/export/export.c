#include "minishell.h"

//export maobe=kitten, if maobe=cat before, now need to change the value
int replace_var_value(char **env, char *s)
{
	int i;
	int j;
	char *new_v;

	i = 0;
	j = -1;
	while (s[i] && s[i] != '=')
		i++;
	while (env[++j])
	{
		if (!ft_strncmp(env[j], s, i + 1))
		{
			new_v = ft_malloc_and_copy(s);
			free_str(env[j]);
			env[j] = new_v;
			return (1);
		}
	}
	return (0);
}

void add_new_var_in_env(char *str, t_mini *sh)
{
	int i;
	int j;
//	char *tmp;

	i = 0;
	j = 0;
//	tmp = NULL;
	while (str[i] && str[i] != '=')
		i++;
	while (sh->env[j])
	{
		if (ft_strncmp(sh->env[j], str, i + 1))
			j++;
		else
			return ;
	}
	ft_envadd(str, sh);
}

/*check var is inside ENV or not, if not add var and its value in ENV*/
void export_add_var(char *var_value, t_mini *sh)
{
	if (!replace_var_value(sh->env, var_value))
		add_new_var_in_env(var_value, sh);
}

/*if cmd == "export", show env; if cmd does not have "=", do not do anything;
  if cmd has invalid char, show error message;
  if have "=" check VAR is in ENV or not(if inside,
  change its value, if not add new VAR in ENV)
**
*/
void export(char **arr, t_mini *sh)
{
	int i;

	i = 0;
	//only type: export
	if (ft_tablen(arr) == 1)
	{
		display_env_w_prefix(arr,sh-> env);
		sh->last_return = 0;
	}
	//ep: xibao!=miao
	else
	{
		while (arr[++i])
		{
			if (has_invalid_char_in_env_name(arr[i]))
			{
				show_key_error_message(EXPORT, arr[i]);
				sh->last_return = 1;
			}
			else if (has_equal_sign(arr[i]))
				export_add_var(arr[i], sh);
		}
	}
}
