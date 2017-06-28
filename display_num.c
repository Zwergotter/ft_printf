/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:41:21 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/28 22:44:52 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void minus_flag(t_lst *list, t_one *one, char **saved)
{
	if (one->sign == '-')
	{
		bufferize_c(saved, one->sign, 1, list);
		one->dif_width--;
	}
	if (one->dif_pre > 0)
		bufferize_c(saved, '0', one->dif_pre, list);
	bufferize_str(saved, one->new, list);
	if (one->dif_width > 0)
		bufferize_c(saved, one->c, one->dif_width, list);
}
// dans fonction a faire qui reprendra tout, changer les lettres low to up si besoin et mettre ca dans buf

void other_flags(t_lst *list, t_one *one, char **saved)
{
	if ((list->flag == ' ' && one->str[0] != '-' && (list->pre == '.' ||
		list->width < one->len)))
		bufferize_c(saved, ' ', 1, list);
	if (one->dif_width > 0)
		bufferize_c(saved, one->c, one->dif_width, list);
	if (list->flag == '+'|| one->sign == '-')
	{
		bufferize_c(saved, one->sign, 1, list);
		one->dif_width--;
	}
	if (one->hash && one->new[0] != '0')
		bufferize_str(saved, one->hash, list);
	if (one->dif_pre > 0)
		bufferize_c(saved, '0', one->dif_pre, list);
	bufferize_str(saved, one->new, list);
}

/*
** Ajout du 0x pour adresse ainsi que pour # a rajouter quand on bufferisera
** plus de travail aussi quant a la maniere de faire gerer les flags comme 0 avec
** adresse ou bien la longueur et la precision
*/

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
	if (list->type == UINT_MAXT || list->type == VOID)
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

void	display_number(t_lst *list, va_list ap, t_one *one, char **saved)
{
	if (((list->spe == 'x' || list->spe == 'X' || list->spe == 'o') && list->flag == '#') || list->spe == 'p') 
		one->hash = (list->spe == 'o' ? "0" : "0x");
	(list->spe == 'd' || list->spe == 'i' ? type_decimal(list, ap, one) :
		type_other(list, ap, one));
	one->len = ft_strlen(one->str);
	one->sign = (one->str[0] == '-' ? '-' : '+');
	one->new = (one->sign == '-' ? ft_strsub(one->str, 1, one->len - 1) :
			one->str);
	if (list->i_pre && list->i_pre > one->len)
		one->dif_pre = list->i_pre - one->len;
	if (list->width > list->i_pre && list->width > one->len)
		one->dif_width = list->width - (one->dif_pre + one->len)  - (one->str[0]
				== '-' || list->flag == ' ' || list->flag == '+' ? 1 : 0) - ft_strlen(one->hash);
	one->c = (list->flag == '0' && !list->pre ? '0' : ' ');
	if (list->flag == '-')
		minus_flag(list, one, saved);
	else
		other_flags(list, one, saved);
}
