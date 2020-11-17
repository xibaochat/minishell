#include "minishell.h"

static void	show_cat_1(void)
{
	ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s█%s▒%s█▀%s\n", B, DF, B,
			 CYAN, B, DF);
	ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s█▀%s\n", B, DF, B, DF);
	ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s\n", B, DF, B, DF);
	ft_printf(" %s▌%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▐ %s\n", B, DF, B, DF);
	ft_printf(" %s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s\n", B, DF, B, DF);
	ft_printf("  %s▌%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▐%s\n", B, DF, B, DF);
	ft_printf("  %s▐▄%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▄▌%s\n", B, DF, B, DF);
	ft_printf("    %s▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀%s\n", B, DF);
}

void	show_cat(void)
{
	ft_printf("   %s▐▀▄%s      %s ▄▀▌%s %s ▄▄▄▄▄▄▄%s\n", B, DF, B, DF, B, DF);
	ft_printf("  %s ▌%s▒▒%s▀▄▄▄▄▄▀%s▒▒%s▐▄▀▀%s▒%s██%s▒%s██%s▒%s▀▀▄%s\n",
			B, DF, B, DF, B, DF, B, DF, B, DF, B, DF);
	ft_printf("  %s▐%s▒▒▒▒%s▀%s▒%s▀%s▒%s▀%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▀▄%s\n", B, DF, B,
			DF, B, DF, B, DF, B, DF);
	ft_printf("  %s▌%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▄%s▒▒▒▒▒▒▒▒▒▒▒▒%s▀▄%s\n", B, DF,
			BLUE, DF, B, DF);
	ft_printf("%s▀█%s▒▒▒%s█▌%s▒▒%s█%s▒▒%s▐█%s▒▒▒%s▀▀%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s\n",
			BLUE, DF, P, DF, GR, DF, P, DF, BLUE, DF, B, DF);
	ft_printf("%s▀▌%s▒▒▒▒▒▒%s▀%s %s▀%s▒▒▒▒▒▒%s▀▀▀%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▐%s  %s▄▄%s\n",
			BLUE, DF, GR, GREY, GR, DF, BLUE, DF, B, DF, B, DF);
	ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s▄█%s▒%s%s█%s\n", B, DF,
			B, B, CYAN, DF, B, DF);
	show_cat_1();
}
