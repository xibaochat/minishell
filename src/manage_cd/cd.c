#include "minishell.h"

/*if the given path cant accesible,
**show the err message
*/
void cd_error_message(char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_w_new_line_fd(str, 2);
}


int cd_to_current_dir_opt(char **arr)
{
	return (arr[1] &&
			!ft_strcmp(arr[1], "."));
}

/*
** Update PWD et OLDPWD env var, and change working
** directory based on HOME env var value
*/
void cd_to_home(t_mini *sh, char *curr_p)
{
	char *path;
	char *dest;

	path = NULL;
	if (!(path = ft_find_env(ENV_HOME, sh->env)))
	{
		ft_putstr_w_new_line_fd(CD_HOME_ERR, 2);
		sh->last_return = 1;
	}
	else
	{
		dest = ft_malloc_and_copy(path);
		go_to_required_directory(sh, dest, curr_p);
	}
}

/*extract oath apres cd, analyse in 4 situation: 1. Multipe destation (cd $PWD $OLDPWD $fdewjehr(path does not exist))
  2.cd to home 3. cd to currect 4. cd to a given directory
  in step 3 and 4, change value of PWD, OLDPWD in EBV
 */
void ft_cd(char **arr, t_mini *sh)
{
	char *curr_p;
	char *valid_path;

	//if env no PWD, OLDPWD, set
	init_env_var(sh);

	//manage cas: cd $dewd $OLDPWD $PWD, has multiple destinations
	if (has_multi_valid_arg(arr) > 1)
	{
		ft_putstr_w_new_line(strerror(EINVAL));
		sh->last_return = 1;
	}
	//manage: cd .
	else if (cd_to_current_dir_opt(arr))
		;
	//situation cd $drewrfd $OLDPWD, if the varis "\0", the go home
	// unset OLDPWD PWD, then cd $PWD
	else
	{
		curr_p = getcwd(NULL, 0);
		if (is_go_home_opt(arr, sh))
			cd_to_home(sh, curr_p);
		else
		{
			valid_path = ft_malloc_and_copy(extract_target_path(arr));
			go_to_required_directory(sh, valid_path, curr_p);
		}
	}
}
