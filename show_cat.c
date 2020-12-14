/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:44:22 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:44:23 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_animals(char *ani, char *age)
{
	if (!ft_strcmp(ani, "sophie"))
		sophie_la_girafe(ft_atoi(age));
	if (!ft_strcmp(ani, "bao"))
		show_cat();
}

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

void		show_cat(void)
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
	ft_printf("%s▀▌%s▒▒▒▒▒▒%s▀%s %s▀%s▒▒▒▒▒▒", BLUE, DF, GR, GREY, GR, DF);
	ft_printf("%s▀▀▀%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▐%s  %s▄▄%s\n", BLUE, DF, B, DF, B, DF);
	ft_printf("%s▐%s▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒%s▌%s▄█%s▒%s%s█%s\n",
			B, DF, B, B, CYAN, DF, B, DF);
	show_cat_1();
}
