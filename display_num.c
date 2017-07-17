/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:41:21 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/17 21:49:33 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
** Function to display number if flag is minus
*/

void minus_flag(t_lst *list, t_one *one)
{
	if ((one->hash && one->new[0] != '0')|| (list->type == VOID &&
		one->new[0] == '0'))
		write_str(one->hash, list);
	if (list->spe == 'X')
		one->new = upper_string(one->new);
	if (one->sign == '-' || list->sign)
	{
		write_c(one->sign, 1, list);
		if (one->sign == '+')
			one->dif_width--;
	}
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
	if (list->sign == '+' && one->sign == '+' && !list->flag)
		one->dif_width--;
	if (list->spe == 'X')
	{
			one->new = upper_string(one->new);
			if (one->hash && one->new[0] != '0')
				one->hash = upper_string(one->hash);
	}
	if ((list->flag == ' ' && one->str[0] != '-' && (one->str[0] == '0' || list->pre == '.' ||
		list->width < one->len)) && one->signed_nb)
		write_c(' ', 1, list);
	if ((one->hash && one->c == '0' && one->new[0] != '0') || (list->zero == '0' && list->type == VOID && one->new[0] == '0'))
		write_str(one->hash, list);
	if (one->dif_width > 0 && one->c == ' ')
		write_c(one->c, one->dif_width, list);
	if ((one->sign && ((list->flag == '+' && one->signed_nb) || list->sign)) || one->sign == '-')
	{
		write_c(one->sign, 1, list);
		if (one->sign == '+' && (one->str[0] != '0' && !list->sign))
			one->dif_width--;
	}
	if (one->dif_width > 0 && one->c == '0')
		write_c(one->c, one->dif_width, list);
	if ((one->hash && one->c == ' ' && one->new[0] != '0') || (list->type == VOID && one->new[0] == '0' && !list->zero))
		write_str(one->hash, list);
	if (one->dif_pre > 0)
		write_c('0', one->dif_pre, list);
	write_str(one->new, list);
}

/*
** Function for all elements that are unsigned numbers in order to 
** be able to extract the argument's value
*/

void 	nb_unsigned(t_lst *list, va_list ap, t_one *one)
{	
	uintmax_t number;
	int base;

	base = 10;
	if (list->spe != 'u' && list->spe != 'U')
		base = (list->spe == 'o' || list->spe == 'O' ? 8 : 16);
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

void 	nb_signed(t_lst *list, va_list ap, t_one *one)
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
	one->str = ft_itoa_base(number < 0 ? -number : number, 10,
		number >= 0 ? 0 : 1);
	one->signed_nb = 1;
}

void	display_number(t_lst *list, va_list ap, t_one *one)
{
	(list->spe == 'd' || list->spe == 'D' || list->spe == 'i' ? nb_signed(list, ap, one) :
		nb_unsigned(list, ap, one));
	one->len = ft_strlen(one->str);
	if (list->spe != 'o' && list->spe != 'O' && list->spe != 'u' && list->spe != 'U')
		one->sign = (one->str[0] == '-' ? '-' : '+');
	one->new = (one->sign == '-' ? ft_strsub(one->str, 1, one->len - 1) :
			one->str);
	if (list->pre && (ft_strcmp(one->new, "0") == 0) && !list->i_pre)
	{
		one->new = " ";
		if (!list->i_pre && !list->width)
			one->new = "";
	}
	if ((list->spe == 'o' || list->spe == 'O' || ((list->spe == 'x' || list->spe == 'X') && one->new[0] != '\0')) || list->type == VOID)
	{
		if (list->hash == '#' || list->spe == 'p')
			one->hash = ((list->spe == 'o' || list->spe == 'O') ? "0" : "0x");
	}
	if (list->i_pre && list->i_pre > one->len - (one->sign == '-' ? 1 : 0))
		one->dif_pre = list->i_pre - (one->len - (one->sign == '-' ? 1 : 0)) - (list->spe == 'o' ? ft_strlen(one->hash) : 0);
	if (list->width > list->i_pre && list->width > one->len)
		one->dif_width = list->width - (one->dif_pre + one->len)  - (list->flag == ' '  ? 1 : 0) - ft_strlen(one->hash) -
	((list->flag == '+') && one->sign == '+' && (list->spe != 'u' && list->spe != 'U') ? 1 : 0);
	one->c = ((list->zero == '0' && list->flag != '-') && !list->pre ? '0' : ' ');
	if (list->flag == '-')
		minus_flag(list, one);
	else
		other_flags(list, one);
}
