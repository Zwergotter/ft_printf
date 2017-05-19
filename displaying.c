/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:48:22 by edeveze           #+#    #+#             */
/*   Updated: 2017/05/15 19:16:57 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

// toute mettre dans une chaine et non pas affichage au fur et a mesure???
// signe a une influence sur width(la longueur) mais pas sur precision
// si precision > length -> nb zeros a ecrire = precision - length (- 1 si signe ou si flag espace existe)
// si width > precision -> nb d'espaces a ecrire = width - (precision > length ? precision ; length)  -- signe et flag espace ne changent pas ce nombre(ne lui enleve pas un charactere, un 0, a afficher). il faut donc les rajouter en plus

void finale(t_lst *list, char *str)
{
	char sign;
	char *new;
	int len;
	int diff_pre;
	int diff_width;

	sign = '\0';
	diff_pre = 0;
	diff_width = 0;
	len = ft_strlen(str);
	if (list->type == INT)
		sign = (str[0] == '-' ? '-' : '+');
	new = (sign ? ft_strsub(str, 1, len - 1) : str);
	if (list->type == INT && list->precision && list->precision > len)
		diff_pre = list->precision - len - (str[0] == '-' || list->flag == ' ' || list->flag == '+' ? 1 : 0);
	if (list->width > list->precision)
		diff_width = list->width - list->precision;
	if (list->flag != '-' && diff_width > 0)
	{
		if ((list->flag == ' ' && list->type == ARG_STR) || (list->flag == ' ' && str[0] != '-'))
		{
			write(1, " ", 1);
			list->nb += 1;
		}
		if (list->type == INT && (list->flag == '+'|| sign == '-'))
		{
			write(1, &sign, 1);
			list->nb += 1;
			diff_width--;
		}
		if (diff_pre > 0)
		{
			while (diff_pre-- > 0)
			{
				write(1, "0",  1);
				list->nb += 1;
			}
		}
		ft_putstr(new);
		while (diff_width-- > 0)
		{
			write(1, " ",  1);
			list->nb += 1;
		}
	}
	else
	{
		// printf("FLAG IS - : flag is %c and diff is %d\n", list->flag, diff);
		while (diff_width-- > 0)
		{
			write(1, " ",  1);
			list->nb += 1;
		}
		if (list->type == INT && sign == '-')
		{
			write(1, &sign, 1);
			list->nb += 1;
			diff_width--;
		}
		if (diff_pre > 0)
		{
			while (diff_pre-- > 0)
			{
				write(1, "0",  1);
				list->nb += 1;
			}
		}
		ft_putstr(new);
	}
	list->nb = list->nb + ft_strlen(new);
	free(new);
}

/*
** Ajouter les options (largeur, flags et precision)
*/
/* peut etre plus malin de faire une fonction avec les differents ajouts a la string initiale et ensuite de prendre le nombre de char pour le list->nb*/

void	display_int(t_lst *list, va_list ap)
{
	char *str;

	str = (list->type == INT ? ft_itoa(va_arg(ap, int)) : ft_strdup(va_arg(ap, char*)));
	finale(list, str);
	free(str);
}

void	displaying(t_lst *list, va_list ap)
{
	if (list->type == INT || list->type == ARG_STR)
		display_int(list, ap);
}
