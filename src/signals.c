#include "minishell.h"

void	signal_interrupt(int sig)
{
//	signal(SIGINT, SIG_IGN);
	if (g_sh.last_pid != 0)
	{
		errno = 0;
		if (kill(g_sh.last_pid, sig) < 0)
			ft_printf("Can't kill process %d\n%s\n", g_sh.last_pid, strerror(errno));
		ft_printf("Nous venons de INTERRUPT %d\n", g_sh.last_pid);
		manage_input(&g_sh);
	}
	else
		exit(1);
//	signal(SIGINT, &signal_interrupt);
	return ;
}

void	signal_quit(int sig)
{
//	signal(SIGQUIT, SIG_IGN);
	if (g_sh.last_pid != 0)
	{
		ft_printf("Quitting process : %d\n", g_sh.last_pid);
		if (kill(g_sh.last_pid, sig) < 0)
			ft_printf("Can't kill process %d\n%s\n", g_sh.last_pid, strerror(errno));
		ft_printf("Nous venons de QUIT %d\n", g_sh.last_pid);
		manage_input(&g_sh);
	}
//	signal(SIGQUIT, &signal_quit);
	return ;
}

int	manage_signals(void)
{
	if (signal(SIGINT, &signal_interrupt) == SIG_ERR)
		ft_putendl("Error : signal returned SIG_ERR with input : SIGINT\n");
	if (signal(SIGQUIT, &signal_quit) == SIG_ERR)
		ft_putendl("Error : signal returned SIG_ERR with input : SIGQUIT\n");
	return (0);
}
