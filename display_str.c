/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:54:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/28 20:07:42 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void display_str(t_lst *list, va_list ap, t_one *one, char **saved)
{
	one->str = ft_strdup(va_arg(ap, char*));
	one->new = (list->i_pre && list->i_pre < (int)ft_strlen(one->str) ? ft_strsub(one->str, 0, list->i_pre - 1) : one->str);
	one->len = ft_strlen(one->new);
	one->dif_width = list->width - (one->len > list->i_pre ? one->len : list->i_pre);
	if (list->pre && !list->i_pre)
	{
		if (list->width)
			(list->flag == '0' ? bufferize_c(saved, '0', list->width, list) : bufferize_c(saved, ' ', list->width, list));
	}
	else
	{
		if (one->dif_width > 0)
		{
			if (list->flag == '-')
			{
				bufferize_str(saved, one->new, list);
				bufferize_c(saved, ' ', one->dif_width, list);
			}
			else
			{
				(list->flag == '0' ? bufferize_c(saved, '0', one->dif_width, list) : bufferize_c(saved, ' ', one->dif_width, list));
				bufferize_str(saved, one->new, list);
			}
		}
		else
			bufferize_str(saved, one->new, list);
	}
}

void display_char(t_lst *list, int nb, char **saved)
{
	char fill;

	fill = (list->flag == '0' ? '0' : ' ');
	if (list->flag != '#')
	{
		if (list->width && list->flag != '-')
			bufferize_c(saved, fill, list->width - 1, list);
		bufferize_c(saved, nb, 1, list);
		if (list->width && list->flag == '-')
			bufferize_c(saved, fill, list->width - 1, list);
	}
	else
		return ;
}
