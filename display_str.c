/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:54:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/12 17:23:22 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void display_str(t_lst *list, va_list ap, t_one *one)
{
	char *str;

	str = va_arg(ap, char*);
	if (!str)
	{
		if (!list->width)
		{
			write_str("(null)", list);
			return ;
		}
	}
	if (str)
	{
		one->str = ft_strdup(str);
		one->new = (list->i_pre && list->i_pre < (int)ft_strlen(one->str) ? ft_strsub(one->str, 0, list->i_pre) : one->str);
		one->len = ft_strlen(one->new);
	}
	ft_putnbr(one->dif_width);
	ft_putstr("is dif_width\n");
	one->dif_width = list->width;
	ft_putnbr(one->dif_width);
	ft_putstr("is dif_width\n");
	if (one->len)
		one->dif_width -= one->len;
		// one->dif_width -= (one->len > list->i_pre ? one->len : list->i_pre);
	ft_putnbr(one->dif_width);
	ft_putstr("is dif_width\n");
	if (list->pre && !list->i_pre)
	{
		if (list->width)
			((list->zero == '0' && list->flag != '-') ? write_c('0', list->width, list) : write_c(' ', list->width, list));
	}
	else
	{
		if (one->dif_width > 0)
		{
			if (list->flag == '-')
			{
				if (one->new)
					write_str(one->new, list);
				write_c(' ', one->dif_width, list);
			}
			else
			{
				((list->zero == '0' && list->flag != '-') ? write_c('0', one->dif_width, list) : write_c(' ', one->dif_width, list));
				if (one->new)
					write_str(one->new, list);
			}
		}
		else
		{
			if (one->new)
					write_str(one->new, list);
		}
	}
}

void display_char(t_lst *list, int nb)
{
	char fill;
	char c;

	c = nb - 0;
	fill = ((list->zero == '0' && list->flag != '-') ? '0' : ' ');
	if (list->flag != '#')
	{
		if (list->width && list->flag != '-')
			write_c(fill, list->width - 1, list);
		write_c(nb, 1, list);
		if (list->width && list->flag == '-')
			write_c(fill, list->width - 1, list);
	}
	else
		return ;
}
