#ifndef MINISHELL_H
# define MINISHELL_H


# define DEFAULT_COLOR  "\033[0;m"
# define BLACK          "\033[1;30m"
# define RED            "\033[1;31m"
# define GREEN          "\033[1;32m"
# define YELLOW         "\033[1;33m"
# define BLUE           "\033[1;34m"
# define PURPLE         "\033[1;35m"
# define CYAN           "\033[1;36m"
# define GREY           "\033[1;37m"
# define WRONG_ARG 22
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct	s_mini
{
	char		**env;
	int			last_return;
}				t_mini;

void	display_ascii_dude();
void	ft_putendl(char *str);
void ft_envadd(char *expt, t_mini *sh);
void	env(t_mini *sh);
void	pwd(t_mini *sh);
void	cd(char **arr, t_mini *sh);
size_t      ft_tablen(char **tab);
int cd_to_current_dir_opt(char **av);
void cd_to_current_dir(t_mini *sh);
void    change_dir(t_mini *sh, char *p);
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
void unset(char **arr, t_mini *sh);
int	get_matched_var_in_env(char **env, char *var);
void	free_str(char *s);
void cpy_env(t_mini *sh, char **env);






#endif
