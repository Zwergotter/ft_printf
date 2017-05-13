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

	str = ft_strdup(va_arg(ap, char*));
	ft_putstr(str);
	list->nb = ft_strlen(str);
	free(str);
}

void	displaying(t_lst *list, va_list ap)
{
	if (list->type == INT)
		display_int(list, ap);
	if (list->type == ARG_STR)
		display_str(list, ap);
}
