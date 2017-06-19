/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:41:21 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/19 16:43:31 by edeveze          ###   ########.fr       */
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

void 	type_other(t_lst *list, va_list ap, t_one *one)
{	
	int base;

	base = 10;
	if (list->spe != 'u')
		base = (list->spe == 'o' ? 8 : 16);
	if (list->type == U_INT || list->type == U_CHAR)
		one->str = 	ft_itoa_base((va_arg(ap, unsigned int)), base);
	if (list->type == USHORT_INT)
		one->str = ft_itoa_base((unsigned short)(va_arg(ap, int)), base);
	if (list->type == ULONG_INT)
		one->str = ft_itoa_base((va_arg(ap, unsigned long)), base);
	if (list->type == SIZE_T)
		one->str = ft_itoa_base(va_arg(ap, size_t), base);
	if (list->type == UINT_MAXT)
		one->str = ft_itoa_base(va_arg(ap, uintmax_t), base);
	if (list->type == ULLONG_INT)
		one->str = unsigned_long_itoa(va_arg(ap, unsigned long long));
}

void 	type_decimal(t_lst *list, va_list ap, t_one *one)
{
	if (list->type == INT || list->type == CHAR)
		one->str = long_itoa((va_arg(ap, int)));
	if (list->type == SHORT_INT)
		one->str = long_itoa((short)(va_arg(ap, int)));
	if (list->type == LONG_INT)
		one->str = long_itoa((va_arg(ap, long)));
	if (list->type == LLONG_INT)
		one->str = long_itoa(va_arg(ap, long long));
	if (list->type == SIZE_T)
		one->str = long_itoa(va_arg(ap, size_t));
	if (list->type == INT_MAXT)
		one->str = long_itoa(va_arg(ap, intmax_t));
	if (list->type == ULLONG_INT)
		one->str = unsigned_long_itoa(va_arg(ap, unsigned long long));
}

void	display_number(t_lst *list, va_list ap, t_one *one)
{
	(list->spe == 'd' || list->spe == 'i' ? type_decimal(list, ap, one) :
		type_other(list, ap, one));
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
