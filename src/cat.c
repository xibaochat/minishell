# include "minishell.h"

static void show_cat_1()
{
	ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s█%s▒%s█▀%s \
	\n", B, DF, B, CYAN, B, DF);
    ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s█▀%s   \
	\n", B, DF, B, DF);
    ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s    \
	\n", B, DF, B, DF);
    ft_printf(" %s▌%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▐ %s    \
	\n", B, DF, B, DF);
    ft_printf(" %s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s     \
	\n", B, DF, B, DF);
    ft_printf("  %s▌%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▐%s      \
	\n", B, DF, B, DF);
    ft_printf("  %s▐▄%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▄▌%s      \
	\n", B, DF, B, DF);
    ft_printf("    %s▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀%s        \
	\n", B, DF);
}


void show_cat()
{
	ft_printf("   %s▐▀▄%s      %s ▄▀▌%s %s ▄▄▄▄▄▄▄%s             \n", B, DF, B,\
	DF, B, DF);
    ft_printf("  %s ▌%s▒▒%s▀▄▄▄▄▄▀%s▒▒%s▐▄▀▀%s▒%s██%s▒%s██%s▒%s▀▀▄%s          \
	\n", B, DF, B, DF, B, DF, B, DF, B, DF, B, DF);
    ft_printf("  %s▐%s▒▒▒▒%s▀%s▒%s▀%s▒%s▀%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▀▄%s        \n", \
	B, DF,B, DF,B, DF,B, DF, B, DF);
    ft_printf("  %s▌%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▄%s▒▒▒▒▒▒▒▒▒▒▒▒%s▀▄%s      \n", B, DF, \
	YELLOW, DF,B, DF);
    ft_printf("%s▀█%s▒▒▒%s█▌%s▒▒%s█%s▒▒%s▐█%s▒▒▒%s▀%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s     \
	\n", B, DF, P, DF,  GR, DF, P, DF, YELLOW, DF, B, DF);
    ft_printf("%s▀▌%s▒▒▒▒▒▒%s▀%s %s▀%s▒▒▒▒▒▒%s▀▀%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▐%s  %s▄▄%s\
	\n", B, DF, GR, GREY, GR, DF, CYAN , DF, B, DF,  B, DF);
    ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s▄█%s▒%s%s█%s\
	\n", B, DF, B, B, CYAN, DF, B, DF);
	show_cat_1();
}
