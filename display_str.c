/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:54:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/08 22:54:18 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void display_str(t_lst *list, va_list ap, t_one *one)
{
	int i;

	i = 0;
	one->str = ft_strdup(va_arg(ap, char*));
	one->new = (list->i_pre && list->i_pre < (int)ft_strlen(one->str) ? ft_strsub(one->str, 0, list->i_pre) : one->str);
	one->len = ft_strlen(one->new);
	one->dif_width = list->width - (one->len > list->i_pre ? one->len : list->i_pre);
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
				write_str(one->new, list);
				write_c(' ', one->dif_width, list);
			}
			else
			{
				((list->zero == '0' && list->flag != '-') ? write_c('0', one->dif_width, list) : write_c(' ', one->dif_width, list));
				write_str(one->new, list);
			}
		}
		else
			write_str(one->new, list);
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

