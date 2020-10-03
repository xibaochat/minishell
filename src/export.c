#include "minishell.h"

int ft_putstr_until(char *s, char c)
{
    int i;

    i = 0;
    while (s[i] != c && s[i])
        ft_putchar(s[i++]);
    return (i);
}

void display_env_w_prefix(char **av, char **env)
{
	int i;
	char *ptr;

	i = 0;
	if (ft_tablen(av) == 1)
    {
        i = 0;
        while (env[i])
        {
            ft_putstr("declare -x ");
            ft_putstr_until(env[i], '=');
            ft_putstr("=\"");
            ptr = ft_strchr(env[i++], '=');
            if (ptr)
                ft_putstr(ptr + 1);
            ft_putendl("\"");
        }
    }
}

int	ft_nomodif(char **env, char *var)
{
	int	i;
	int	check1;
	int	check2;

	i = 0;
	check1 = 1;
	check2 = 1;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var))
			&& env[i][ft_strlen(var)] == '=')
			check1 = 0;
		i++;
	}
	if (!ft_strchr(var, '='))
		check2 = 0;
	return (check1 + check2);
}

void replace_var_value(char **env, char *s)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = -1;
	tmp = NULL;
	while (s[i] && s[i] != '=')
		i++;
	while (env[++j])
	{
		if (!ft_strncmp(env[j], s, i + 1))
		{
			tmp = env[j];
			env[j] = s;
			free(tmp);
		}
	}
}

void ft_envadd(char **envp, char *expt, t_mini *sh)
{
    int i;
    char    **env;

    i = 0;
    while (envp[i])
        i++;
    if (expt != NULL)
        i++;
    if (!(env = malloc(sizeof(char *) * (i + 1))))
	{
		ft_putstr_fd("Fail Malloc\n", 2);
		exit(-1);
	}
    i = -1;
    while (envp[++i])
        env[i] = ft_strdup(envp[i]);
    if (expt != NULL)
		env[i++] = ft_strdup(expt);
    env[i] = NULL;
	sh->env = env;
//	ft_tabfree(envp);
}

void    ft_tabfree(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        tab[i] = NULL;
        free(tab[i++]);
    }
    free(tab);
    return ;
}

void add_new_var_in_env(char *str, t_mini *sh)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (str[i] && str[i] != '=')
		i++;
	while (sh->env[j])
	{
		if (ft_strncmp(sh->env[j], str, i + 1))
			j++;
		else
			return ;
	}
	ft_envadd(sh->env, str, sh);
}

void export_add_var(char *var_value, t_mini *sh)
{
	char *tmp;
	char *s;

	if (invalid_export_var_val(var_value))
	{
		if (!has_no_equal_sign(var_value))
		{
			ft_putstr_fd(strerror(WRONG_ARG), 2);
			ft_putstr_fd("\n", 2);
		}
		return ;
	}
	//else if (!ft_nomodif(sh->env, var_value))
	//	return ;
	replace_var_value(sh->env, var_value);
	add_new_var_in_env(var_value, sh);
}

void export(char **arr, t_mini *sh)
{
	if (ft_tablen(arr) > 2)
    {
        ft_putstr(strerror(WRONG_ARG));
        return ;
    }
	if (ft_tablen(arr) == 1)
		display_env_w_prefix(arr,sh-> env);
	else
		export_add_var(arr[1], sh);
}
