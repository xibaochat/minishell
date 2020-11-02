#ifndef MINISHELL_H
# define MINISHELL_H

# define SINGLE 39
# define DOUBLE 34
# define EXPORT 0
# define UNSET 1
# define DF  "\033[0;m"
# define BLACK          "\033[1;30m"
# define RED            "\033[1;31m"
# define GR          "\033[1;32m"
# define YELLOW         "\033[1;33m"
# define B           "\033[1;34m"
# define P         "\033[1;35m"
# define CYAN           "\033[1;36m"
# define GREY           "\033[1;37m"
# define WHITE "\033[;0m"
# define BLINK "\e[5m"
# define B_YE  "\e[38;5;11m"
# define ORANGE "\e[38;5;209m"
# define BOLD_GR "\e[1;92m"
# define PINK "\e[38;5;198m"
# define BLUE "\e[38;5;21m"

# define WRONG_ARG 22
# define VAL_ERROR ": not a valid identifier"
# define BIN_ERROR ": No such file or directory"
# define CMD_NO_FD ": command not found"

# define ENV_USER "USER="
# define ENV_PATH "PATH="
# define ENV_HOME "HOME="
# define ENV_PWD "PWD="
# define ENV_OLDPWD "OLDPWD="
# define BASIC_ENV_USER "USER=maobe"
# define HOME_ERROR "%s/!\\ NO HOME DEFINE /!\\ \n%s"


# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>

# include "libft.h"

typedef struct	s_mini
{
	char		*line;
	char		**env;
	int			last_pid;
	int			ctrl_c;
	int			is_cmd;
	int			last_return;
	int			exit_v;
	int			cmd_is_bin;
}				t_mini;


/*
** This global variable is needed to deal with signals (cf. signals.c)
*/

void	show_cat();
void	display_ascii_dude();
int	manage_signals();
void	manage_input(t_mini *sh);
void	ft_putendl(char *str);
void ft_envadd(char *expt, t_mini *sh);
void	env(t_mini *sh);
void	pwd(t_mini *sh);
void	cd(char **arr, t_mini *sh);
void	echo(char **arr);
char	*ft_find_env(char *name, char **env);
size_t      ft_tablen(char **tab);
int cd_to_current_dir_opt(char **av);
void cd_to_current_dir(t_mini *sh);
void    change_dir(t_mini *sh, char *p);
void change_env_var_value(char **env, char *new_p, char *var);
void    change_dir_for_other_opts(t_mini *sh, char *path, char *old_p);
void cd_error_message(char *str);
void export(char **arr, t_mini *sh);
int has_invalid_char_in_env_name(char *str);
int has_equal_sign(char *s);
void    ft_tabfree(char **tab);
void show_export_error_message(char *s);
void display_env_w_prefix(char **av, char **env);
void unset(char **arr, t_mini *sh);
int	get_matched_var_in_env(char **env, char *var);
void cpy_env(t_mini *sh, char **env);
char *find_full_binary_path(char *cmd, t_mini *sh);
int print_prompt(t_mini *sh);
void check_quote_close(char **arr, t_mini *sh);
void show_key_error_message(int key, char *s);
void show_welcome_mes();
void replace_var_sub_by_true_value(char **arr, t_mini *sh);
char	*get_full_cmd_path(char *cmd, t_mini *sh);
void    ft_exit(char **split_input, t_mini *sh);
void ft_signal(t_mini *sh);
void init_sh(char **env);
t_mini **get_sh();
int get_nb_digit(int nb);
void manage_question_mark(char **str, int j, int n, t_mini *sh);
char *extract_cmd_from_bin_cmd(int index, char *cmd);
char * manage_binary_cmd(char *cmd, t_mini *sh);
int get_bin_directory_index(char *str);
void show_error_message(char *cmd, char *err, t_mini *sh);
char    *check_cmd_and_return_full_bin_path(char *cmd, char **bin_path);
int is_binary_path(char *s);
void free_var(t_mini **sh);
void parent_process(t_mini *sh);
void child_process(char *bin_path, char **split_input, t_mini *sh);









#endif
