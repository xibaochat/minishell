#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"

typedef struct	s_mini
{
	char		**env;
}				t_mini;

void	display_ascii_dude();
void	ft_putendl(char *str);
char	**ft_envadd(char **envp, char *expt);
void	env(t_mini *sh);
void	pwd(t_mini *sh);
void	cd(char **arr, t_mini *sh);
size_t      ft_tablen(char **tab);
int cd_to_home_opt(char **arr);
int cd_to_current_dir_opt(char **av);
int cd_to_pre_dir_opt(char **av);
void cd_to_home(t_mini *sh);
void cd_to_current_dir(void);
void cd_to_pre_dir(char **arr, t_mini *sh);
void    change_dir(char *path);
char	*get_extracted_path(char **av, char *env_var);


#endif
