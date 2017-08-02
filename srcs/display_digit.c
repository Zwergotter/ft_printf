/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:41:21 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 19:00:25 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Function to display number if flag is minus
*/

void	minus_flag(t_lst *list, t_one *one)
{
	if ((one->hash && one->oth[0] != '0') || (list->type == VOID &&
		one->oth[0] == '0'))
		write_str(one->hash);
	if (list->sp == 'X')
		upper_string(one->oth);
	if (one->sign == '-' || list->sign)
	{
		write_c(one->sign, 1);
		if (one->sign == '+')
			one->width--;
	}
	if (one->pre > 0)
		write_c('0', one->pre);
	write_str(one->oth);
	if (one->width > 0)
		write_c(one->c, one->width);
}

/*
** Function to display number if flag is anything but minus
*/

void	other_flags(t_lst *list, t_one *one)
{
	if (list->sign == '+' && one->sign == '+' && !list->flag)
		one->width--;
	if (list->sp == 'X')
	{
		upper_string(one->oth);
		if (one->hash && one->oth[0] != '0')
			upper_string(one->hash);
	}
	if ((list->flag == ' ' && one->str[0] != '-' && (one->str[0] == '0' ||
		list->pre == '.' || list->width < one->len)) && one->signed_nb)
		write_c(' ', 1);
	if ((one->hash && one->c == '0' && one->oth[0] != '0') || (list->zero &&
		list->type == VOID && one->oth[0] == '0'))
		write_str(one->hash);
	if (one->width > 0 && one->c == ' ')
		write_c(one->c, one->width);
	if ((one->sign && ((list->flag == '+' && one->signed_nb) || list->sign))
		|| one->sign == '-')
	{
		write_c(one->sign, 1);
		if (one->sign == '+' && (one->str[0] != '0' && !list->sign))
			one->width--;
	}
	if (one->width > 0 && one->c == '0')
		write_c(one->c, one->width);
	if ((one->hash && one->c == ' ' && one->oth[0] != '0') ||
		(list->type == VOID && one->oth[0] == '0' && !list->zero))
		write_str(one->hash);
	if (one->pre > 0)
		write_c('0', one->pre);
	write_str(one->oth);
}

void	display_number(t_lst *lst, va_list ap, t_one *one)
{
	attributing(lst, ap, one);
	if (lst->flag == '-')
		minus_flag(lst, one);
	else
		other_flags(lst, one);
}
