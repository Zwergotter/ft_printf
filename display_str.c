/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:54:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/07 16:54:53 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void display_str(t_lst *list, va_list ap, t_one *one)
{
	one->str = ft_strdup(va_arg(ap, char*));
	one->new = (list->i_pre && list->i_pre < list->len? ft_strsub(one->str, 0, list->i_pre - 1) : one->str);
	one->len = ft_strlen(one->new);
	one->diff_width = list->width - (list->len > list->i_pre ? list->i_pre : list->len);
	if (list->pre && !list->i_pre) //si precicion existe mais qu'aucun nombre n'a ete precise
	{
		if (list->width)//si une largeur a ete precisee
			(list->flag == '0' ? write_char('0', list->width) : write_char(' ', list->width));
		list->nb = (list->width ? list->width : 0);
	}
	else
	{
		if (list->width > list->len && list->width > list->i_pre)// si largeur precisee est plus grande que longueur et precision
		{
			if (list->flag == '-')
			{
				ft_putstr(one->new);
				write_char(' ', one->diff_width);
			}
			else
			{
				(list->flag == '0' ? write_char('0', one->diff_width) : write_char(' ', one->diff_width));
				ft_putstr(one->new);
			}
		}
		else
			ft_putstr(one->new);
		list->nb = (list->width > one->len ? list->width : one->len);
	}
}
