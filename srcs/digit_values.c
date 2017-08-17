/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 18:51:55 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/13 18:34:50 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Function for all elements that are unsigned numbers in order to
** be able to extract the argument's value
*/

void	nb_unsigned(t_lst *list, va_list ap, t_one *one)
{
	uintmax_t	nb;
	int			base;

	base = 10;
	if (list->sp != 'u' && list->sp != 'U')
		base = (list->sp == 'o' || list->sp == 'O' ? 8 : 16);
	if (list->type == U_CHAR)
		nb = (unsigned char)va_arg(ap, unsigned int);
	if (list->type == U_INT)
		nb = va_arg(ap, unsigned int);
	if (list->type == USHORT_INT)
		nb = (unsigned short)va_arg(ap, unsigned int);
	if (list->type == ULONG_INT)
		nb = va_arg(ap, unsigned long int);
	if (list->type == ULLONG_INT)
		nb = va_arg(ap, unsigned long long int);
	if (list->type == SIZE_T)
		nb = va_arg(ap, size_t);
	if (list->type == UINT_MAXT || list->type == VOID)
		nb = va_arg(ap, uintmax_t);
	one->str = ft_itoa_base(nb, base, 0);
}

/*
** Function for all elements that are signed numbers in order to
** be able to extract the argument's value
*/

void	nb_signed(t_lst *list, va_list ap, t_one *one)
{
	intmax_t nb;

	if (list->type == CHAR)
		nb = (char)va_arg(ap, int);
	if (list->type == INT)
		nb = va_arg(ap, int);
	if (list->type == SHORT_INT)
		nb = (short)va_arg(ap, int);
	if (list->type == LONG_INT)
		nb = va_arg(ap, long int);
	if (list->type == LLONG_INT)
		nb = va_arg(ap, long long int);
	if (list->type == SIZE_T)
		nb = va_arg(ap, size_t);
	if (list->type == INT_MAXT)
		nb = va_arg(ap, intmax_t);
	one->str = ft_itoa_base(nb < 0 ? -nb : nb, 10, nb >= 0 ? 0 : 1);
	one->signed_nb = 1;
}

/*
** Deals with options found, in order to attribute corresponding values or
** calculate precision and width.
*/

void	giving_values(t_lst *lst, t_one *one)
{
	if (lst->pre && (ft_strcmp(one->oth, "0") == 0) && !lst->i_pre)
	{
		free(one->oth);
		if (!lst->width)
			one->oth = ft_strdup("");
		else
			one->oth = ft_strdup(" ");
	}
	if (lst->sp == 'o' && lst->sp == 'O' && lst->sp == 'u' && lst->sp == 'U')
		one->sign = '0';
	if ((lst->sp == 'o' || lst->sp == 'O' || ((lst->sp == 'x' ||
		lst->sp == 'X') && one->oth[0] != '\0')) || lst->type == VOID)
	{
		if (lst->hash == '#' || lst->sp == 'p')
			one->hash = ((lst->sp == 'o' || lst->sp == 'O') ? ft_strdup("0") :
				ft_strdup("0x"));
	}
	if (lst->i_pre && lst->i_pre > one->len - (one->sign == '-' ? 1 : 0))
		one->pre = lst->i_pre - (one->len - (one->sign == '-' ? 1 : 0)) -
	(lst->sp == 'o' ? ft_strlen(one->hash) : 0);
	if (lst->width > lst->i_pre && lst->width > one->len)
		one->width = lst->width - (one->pre + one->len) - (lst->flag == ' ' ?
			1 : 0) - ft_strlen(one->hash) - ((lst->flag == '+') && one->sign ==
			'+' && (lst->sp != 'u' && lst->sp != 'U') ? 1 : 0);
}

/*
** Attributing first values to an element t_one
*/

void	attributing(t_lst *lst, va_list ap, t_one *one)
{
	(lst->sp == 'd' || lst->sp == 'D' || lst->sp == 'i' ?
		nb_signed(lst, ap, one) : nb_unsigned(lst, ap, one));
	one->len = ft_strlen(one->str);
	one->c = ((lst->zero && lst->flag != '-') && !lst->pre ? '0' : ' ');
	one->sign = (one->str[0] == '-' ? '-' : '+');
	one->oth = (one->sign == '-' ? ft_strsub(one->str, 1, one->len - 1) :
			ft_strdup(one->str));
	giving_values(lst, one);
}
