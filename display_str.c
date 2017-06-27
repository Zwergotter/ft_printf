/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:54:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/27 16:50:02 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void display_str(char **saved, t_lst *list, va_list ap, t_one *one)
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
				bufferize(saved, one->new, 1);
				bufferize(saved, " ", one->dif_width);
			}
			else
			{
				(list->flag == '0' ? bufferize(saved, "0", one->dif_width) : bufferize(saved, " ", one->dif_width));
				bufferize(saved, one->new, 1);
			}
		}
		else
			bufferize(saved, one->new, 1);
		list->nb = (list->width > one->len ? list->width : one->len);
	}
}

void display_char(char **saved, t_lst *list, int nb)
{
	char fill;
	char c;

	c = nb + '0';
	fill = (list->flag == '0' ? '0' : ' ');
	if (list->flag != '#')
	{
		if (list->width && list->flag != '-')
			bufferize(saved, &fill, list->width - 1);
		bufferize(saved, &c, 1);;//ecrire soit le charactere normal soit les octets donnes par display_wchar
		if (list->width && list->flag == '-')
			bufferize(saved, &fill, list->width - 1);
	}
	else
		return ;
}
