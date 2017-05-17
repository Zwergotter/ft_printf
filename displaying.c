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

void finale(t_lst *list, char *str)
{
	char c;
	int len;
	int diff;

	diff = 0;
	len = ft_strlen(str);
	if (list->precision && list->precision > len)
		diff = list->precision - len;
	if (diff == 0)
		diff = list->width - len;
	c = ' ';
	if (diff > 0 && list->flag != '-')
	{
		if (list->flag == '0')
				c = '0';
		while (diff-- > 0)
				write(1, &c,  1);
	}
	if ((list->flag == ' ' && list->type == ARG_STR) || (list->flag == ' ' && str[0] != '-'))
	{
		write(1, &c, 1);
		list->nb = 1;
	}
	if (list->type == INT && list->flag == '+' && ft_atoi(str) > 0)
	{
		write(1, "+", 1);
		list->nb = 1;
	}
	ft_putstr(str);
	if (list->flag == '-' && diff > 0)
	{
		while (diff-- > len)
			write(1, &c,  1);
	}
	list->nb = list->nb + (len > list->width ? ft_strlen(str)  : list->width);
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
