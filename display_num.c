/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:41:21 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/19 13:55:44 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void minus_flag(t_lst *list, t_one *one)
{
	if (one->sign == '-')
	{
		write(1, &one->sign, 1);
		list->nb += 1;
		one->dif_width--;
	}
	if (one->dif_pre > 0)
	{
		while (one->dif_pre-- > 0)
		{
			write(1, "0",  1);
			list->nb += 1;
		}
	}
	ft_putstr(one->new);
	while (one->dif_width-- > 0)
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
	while (one->dif_width-- > 0)
	{
		write(1, &one->c,  1);
		list->nb += 1;
	}
	if (list->flag == '+'|| one->sign == '-')
	{
		write(1, &one->sign, 1);
		list->nb += 1;
		one->dif_width--;
	}
	while (one->dif_pre-- > 0)
	{
		write(1, "0",  1);
		list->nb += 1;
	}
	ft_putstr(one->new);
}

void 	type_number(t_lst *list, va_list ap, t_one *one)
{
	if (list->type == INT)
		one->str = long_itoa((va_arg(ap, int)));
	if (list->type == U_INT)
		one->str = long_itoa((va_arg(ap, unsigned int)));
	if (list->type == SHORT_INT)
		one->str = long_itoa((short)(va_arg(ap, int)));
	if (list->type == USHORT_INT)
		one->str = long_itoa((unsigned short)(va_arg(ap, int)));
	if (list->type == LONG_INT)
		one->str = long_itoa((va_arg(ap, long)));
	if (list->type == ULONG_INT)
		one->str = long_itoa((va_arg(ap, unsigned long)));
	if (list->type == LLONG_INT)
		one->str = long_itoa(va_arg(ap, long long));
	if (list->type == SIZE_T)
		one->str = long_itoa(va_arg(ap, size_t));
	if (list->type == INT_MAXT)
		one->str = long_itoa(va_arg(ap, intmax_t));
	if (list->type == UINT_MAXT)
		one->str = long_itoa(va_arg(ap, uintmax_t));
	if (list->type == ULLONG_INT)
		one->str = unsigned_long_itoa(va_arg(ap, unsigned long long));
}

void	display_number(t_lst *list, va_list ap, t_one *one)
{
	type_number(list, ap, one);
	one->len = ft_strlen(one->str);
	one->sign = (one->str[0] == '-' ? '-' : '+');
	one->new = (one->sign == '-' ? ft_strsub(one->str, 1, one->len - 1) :
			one->str);
	if (list->i_pre && list->i_pre > one->len) // quelle est l'influence de la precision sur les autres types (est ce quíl y a une influence par ex avec one->string??)
		one->dif_pre = list->i_pre - one->len;
	if (list->width > list->i_pre && list->width > one->len)
		one->dif_width = list->width - (one->dif_pre + one->len)  - (one->str[0]
				== '-' || list->flag == ' ' || list->flag == '+' ? 1 : 0);
	one->c = (list->flag == '0' && !list->pre ? '0' : ' ');
	if (list->flag == '-')
		minus_flag(list, one);
	else
		other_flags(list, one);
	list->nb = list->nb + ft_strlen(one->new);
}
