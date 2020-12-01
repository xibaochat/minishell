#include "minishell.h"

void	show_welcome_mes(void)
{
	char	*s;
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;

	s = "🆆 🅴 🅻 🅲 🅾 🅼 🅴   ";
	s1 = "🆃 🅾   ";
	s2 = "P̅ A̅ D̅ O̅ U̅ E̅";
	s3 = "🅼 🅰 🅾 🅱 🅴 ";
	s4 = " 🅼 🅸 🅽 🅸 🆂 🅷 🅴 🅻 🅻 ";
	ft_printf("\n%s%s%s", B_YE, s, DF);
	ft_printf("%s%s%s", ORANGE, s1, DF);
	ft_printf("%s%s%s%s", BLINK, BOLD_GR, s2, DF);
	ft_printf("  和  ");
	ft_printf("%s%s%s%s", BLINK, PINK, s3, DF);
	ft_printf("%s%s%s\n\n", BLUE, s4, DF);
}
