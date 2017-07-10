/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:41:21 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/10 11:38:29 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
** Function to display number if flag is minus
*/

void minus_flag(t_lst *list, t_one *one)
{
	if (one->hash && one->new[0] != '0')
		write_str(one->hash, list);
	if (list->spe == 'X')
		one->new = upper_string(one->new);
	if (one->sign == '-')
		write_c(one->sign, 1, list);
	if (one->dif_pre > 0)
		write_c('0', one->dif_pre, list);
	write_str(one->new, list);
	if (one->dif_width > 0)
		write_c(one->c, one->dif_width, list);
}

/*
** Function to display number if flag is anything but minus
*/

void other_flags(t_lst *list, t_one *one)
{
	if (list->spe == 'X')
	{
			one->new = upper_string(one->new);
			if (one->hash && one->new[0] != '0')
				one->hash = upper_string(one->hash);
	}
	if ((list->flag == ' ' && one->str[0] != '-' && (list->pre == '.' ||
		list->width < one->len)))
		write_c(' ', 1, list);
	if (one->hash && one->c == '0' && one->new[0] != '0')
		write_str(one->hash, list);
	if (one->dif_width > 0 && one->c == ' ')
		write_c(one->c, one->dif_width, list);
	if (list->flag == '+'|| one->sign == '-')
		{
			write_c(one->sign, 1, list);
			if (one->sign == '+')
				one->dif_width--;
		}
	if (one->dif_width > 0 && one->c == '0')
		write_c(one->c, one->dif_width, list);
	if (one->hash && one->c == ' ' && one->new[0] != '0')
		write_str(one->hash, list);
	if (one->dif_pre > 0)
		write_c('0', one->dif_pre, list);
	write_str(one->new, list);
}

/*
** Function for all elements that are unsigned numbers in order to 
** be able to extract the argument's value
*/

void 	type_other(t_lst *list, va_list ap, t_one *one)
{	
	uintmax_t number;
	int base;

	base = 10;
	if (list->spe != 'u')
		base = (list->spe == 'o' ? 8 : 16);
	if (list->type == U_CHAR)
		number = (unsigned char)va_arg(ap, unsigned int);
	if (list->type == U_INT)
		number = va_arg(ap, unsigned int);
	if (list->type == USHORT_INT)
		number = (unsigned short)va_arg(ap, unsigned int);
	if (list->type == ULONG_INT)
		number = va_arg(ap, unsigned long int);
	if (list->type == ULLONG_INT)
		number = va_arg(ap, unsigned long long int);
	if (list->type == SIZE_T)
		number = va_arg(ap, size_t);
	if (list->type == UINT_MAXT || list->type == VOID)
		number = va_arg(ap, uintmax_t);
	one->str = ft_itoa_base(number, base, 0);
}

/*
** Function for all elements that are signed numbers in order to 
** be able to extract the argument's value
*/

void 	type_decimal(t_lst *list, va_list ap, t_one *one)
{	
	intmax_t number;

	if (list->type == CHAR)
		number = (char)va_arg(ap, int);
	if (list->type == INT)
		number = va_arg(ap, int);
	if (list->type == SHORT_INT)
		number = (short)va_arg(ap, int);
	if (list->type == LONG_INT)
		number = va_arg(ap, long int);
	if (list->type == LLONG_INT)
		number = va_arg(ap, long long int);
	if (list->type == SIZE_T)
		number = va_arg(ap, size_t);
	if (list->type == INT_MAXT)
		number = va_arg(ap, intmax_t);
	one->str = ft_itoa_base(number < 0 ? -number : number, 10, number >= 0 ? 0 : 1);
}

void	display_number(t_lst *list, va_list ap, t_one *one)
{
	(list->spe == 'd' || list->spe == 'i' ? type_decimal(list, ap, one) :
		type_other(list, ap, one));
	one->len = ft_strlen(one->str);
	one->sign = (one->str[0] == '-' ? '-' : '+');
	if (list->spe == 'x' || list->spe == 'X' || list->spe == 'o') 
		{
			if (list->hash == '#' || list->spe == 'p')
				one->hash = (list->spe == 'o' ? "0" : "0x");
		}
	one->new = (one->sign == '-' ? ft_strsub(one->str, 1, one->len - 1) :
			one->str);
	if (list->i_pre && list->i_pre > one->len)
		one->dif_pre = list->i_pre - one->len;
	if (list->width > list->i_pre && list->width > one->len)
		one->dif_width = list->width - (one->dif_pre + one->len)  - (list->flag == ' '  ? 1 : 0) - ft_strlen(one->hash);
	one->c = ((list->zero == '0' && list->flag != '-') && !list->pre ? '0' : ' ');
	if (list->flag == '-')
		minus_flag(list, one);
	else
		other_flags(list, one);
}
