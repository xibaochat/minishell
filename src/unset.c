#include "minishell.h"

char **get_unset_env(char **arr, char **env)
{
	int i;
	int j;
	int lens;
	char *tmp;

	i = 1;
	while (arr[i])
	{
		j = 0;
		while (env[j])
		{
			lens = ft_strlen(arr[i]);
			if (!ft_strncmp(arr[i], env[j], lens)
				&& env[j][lens] && env[j][lens] == '=')
			{
				tmp = env[j];
				env[j] = ft_strnew(1);
				free(tmp);
			}
			j++;
		}
		i++;
	}
	return (env);
}

int get_new_env_nb_var(char **arr, char **env)
{
	char **new_env;
	int i;
	int nb;

	i = 0;
	nb = 0;
	new_env = get_unset_env(arr, env);
	while (new_env[i])
	{
		if (!new_env[i][0])
			nb++;
		i++;
	}
	printf("nb is %d\n\n", nb);
	return (nb);
}

char **init_new_env(char **arr, t_mini *sh)
{
	int nb;
	int j;
	char **new_env;

	nb = get_new_env_nb_var(arr, sh->env);
	new_env = (char **)malloc(sizeof(char *) * (nb + 1));
	j = 0;
	while (j < nb + 1)
		new_env[j++] = NULL;
	return (new_env);
}

int get_nb_var(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void unset(char **arr, t_mini *sh)
{
	char **new_env;
	int nb;
	int i;
	int j;

	j = 0;
	i = 0;
	new_env = init_new_env(arr, sh);
	int n = get_new_env_nb_var(arr, sh->env);
	printf("n is %d\n", n);
	while (j < get_nb_var(sh->env))
	{
		if (sh->env[j] && sh->env[j][0])
		{
			new_env[i] =sh->env[j];
			ft_putstr_w_new_line(new_env[i]);
			i++;
		}
		j++;
	}
	sh->env = new_env;
}
