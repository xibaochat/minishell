#ifndef MINISHELL_H
# define MINISHELL_H

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"

void	display_ascii_dude();
void	ft_putendl(char *str);
char	**ft_envadd(char **envp, char *expt);


#endif
