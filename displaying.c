/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:48:22 by edeveze           #+#    #+#             */
/*   Updated: 2017/05/13 19:48:46 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
** Ajouter les options (largeur, flags et precision)
*/

void	display_int(t_lst *list, va_list ap)
{
	int result;

	result = va_arg(ap, int);
	ft_putnbr(result);
	list->nb = ft_countdigits(result);
}

void	display_str(t_lst *list, va_list ap)
{
	char *str;
	int len;
	int width;

	str = ft_strdup(va_arg(ap, char*));
	len = ft_strlen(str);
	width = list->width;
	if (width)
	{
		while (width-- > len)
			write(1, " ",  1);

	}
	ft_putstr(str);
	list->nb = (len > list->width ? ft_strlen(str)  : list->width);
	free(str);
}

void	displaying(t_lst *list, va_list ap)
{
	if (list->type == INT)
		display_int(list, ap);
	if (list->type == ARG_STR)
		display_str(list, ap);
}
