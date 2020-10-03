#ifndef MINISHELL_H
# define MINISHELL_H

# define WRONG_ARG 22
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"

typedef struct	s_mini
{
	char		**env;
	int nb;
}				t_mini;

void	display_ascii_dude();
void	ft_putendl(char *str);
void ft_envadd(char **envp, char *expt, t_mini *sh);
void	env(t_mini *sh);
void	pwd(t_mini *sh);
void	cd(char **arr, t_mini *sh);
size_t      ft_tablen(char **tab);
int cd_to_home_opt(char **arr);
int cd_to_current_dir_opt(char **av);
int cd_to_pre_dir_opt(char **av);
void cd_to_home(t_mini *sh);
void cd_to_current_dir(t_mini *sh);
void cd_to_pre_dir(char **arr, t_mini *sh);
void    change_dir(t_mini *sh, char *p, char *path);
char	*get_extracted_path(char **av, char *env_var);
void change_env_var_value(char **env, char *new_p, char *var);
void    change_dir_for_other_opts(t_mini *sh, char *path, char *old_p);
void cd_error_message(char *str);
void export(char **arr, t_mini *sh);
int has_no_equal_sign(char *s);
int invalid_export_var_val(char *s);
void    ft_tabfree(char **tab);
void show_export_error_message(char *s);
void display_env_w_prefix(char **av, char **env);
char *rm_quote_in_str(char *s);
int has_quote_in_str(char *s);






#endif
