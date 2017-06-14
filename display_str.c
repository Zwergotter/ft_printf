/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:54:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/14 17:33:26 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void display_str(t_lst *list, va_list ap, t_one *one)
{
	one->str = ft_strdup(va_arg(ap, char*));
	one->new = (list->i_pre && list->i_pre < (int)ft_strlen(one->str) ? ft_strsub(one->str, 0, list->i_pre - 1) : one->str);
	one->len = ft_strlen(one->new);
	one->dif_width = list->width - (one->len > list->i_pre ? one->len : list->i_pre);
	if (list->pre && !list->i_pre)
	{
		if (list->width)
			(list->flag == '0' ? write_char('0', list->width) : write_char(' ', list->width));
		list->nb = (list->width ? list->width : 0);
	}
	else
	{
		if (one->dif_width > 0)
		{
			if (list->flag == '-')
			{
				ft_putstr(one->new);
				write_char(' ', one->dif_width);
			}
			else
			{
				(list->flag == '0' ? write_char('0', one->dif_width) : write_char(' ', one->dif_width));
				ft_putstr(one->new);
			}
		}
		else
			ft_putstr(one->new);
		list->nb = (list->width > one->len ? list->width : one->len);
	}
}

void display_char(t_lst *list, va_list ap)
{
	char c;
	char fill;

	c = va_arg(ap, int);
	fill = (list->flag == '0' ? '0' : ' ');
	if (list->flag != '#')
	{
		if (list->width && list->flag != '-')
			write_char(fill, list->width - 1);
		ft_putchar(c);
		if (list->width && list->flag == '-')
			write_char(fill, list->width - 1);
	}
	else
		return ;
}
