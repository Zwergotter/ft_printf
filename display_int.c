/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:41:21 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/13 16:41:24 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void minus_flag(t_lst *list, t_one *one)
{
	if (list->type == INT && one->sign == '-')
	{
		write(1, &one->sign, 1);
		list->nb += 1;
		one->diff_width--;
	}
	if (one->diff_pre > 0)
	{
		while (one->diff_pre-- > 0)
		{
			write(1, "0",  1);
			list->nb += 1;
		}
	}
	ft_putstr(one->new);
	while (one->diff_width-- > 0)
	{
		write(1, &one->c,  1);
		list->nb += 1;
	}
}

void other_flags(t_lst *list, t_one *one)
{
	if ((list->flag == ' ' && list->type == ARG_STR) || (list->flag == ' ' &&
		one->str[0] != '-' && (list->pre == '.' || list->width < one->len)))
	{
		write(1, " ", 1);
		list->nb += 1;
	}
	while (one->diff_width-- > 0)
	{
		write(1, &one->c,  1);
		list->nb += 1;
	}
	if (list->type == INT && (list->flag == '+'|| one->sign == '-'))
	{
		write(1, &one->sign, 1);
		list->nb += 1;
		one->diff_width--;
	}
	while (one->diff_pre-- > 0)
	{
		write(1, "0",  1);
		list->nb += 1;
	}
	ft_putstr(one->new);
}

/*
** peut etre plus malin de faire une fonction avec les differents ajouts a la string initiale et ensuite de prendre le nombre de char pour le list->nb
*/

void	display_int(t_lst *list, va_list ap, t_one *one)
{
	one->str = (list->type == INT ? ft_itoa(va_arg(ap, int)) : ft_strdup(va_arg(ap, char*)));
	one->len = ft_strlen(one->str);
	if (list->type == INT)
		one->sign = (one->str[0] == '-' ? '-' : '+');
	one->new = (one->sign == '-' ? ft_strsub(one->str, 1, one->len - 1) : one->str);
	if (list->type == INT && list->i_pre && list->i_pre > one->len) // quelle est l'influence de la precision sur les autres types (est ce quíl y a une influence par ex avec one->string??)
		one->diff_pre = list->i_pre - one->len;
	if (list->width > list->i_pre && list->width > one->len)
		one->diff_width = list->width - (one->diff_pre + one->len)  - (one->str[0] == '-' || list->flag == ' ' || list->flag == '+' ? 1 : 0);
	one->c = (list->flag == '0' && !list->pre ? '0' : ' ');
	if (list->flag == '-')
		minus_flag(list, one);
	else
		other_flags(list, one);
	list->nb = list->nb + ft_strlen(one->new);
}
