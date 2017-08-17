/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 17:44:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 14:37:54 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	type_unsigned(t_lst *elem)
{
	elem->type = U_INT;
	if ((ft_strcmp(elem->length, "l")) == 0 || elem->sp == 'U'
		|| elem->sp == 'O')
	{
		elem->type = ULONG_INT;
		return ;
	}
	if ((ft_strcmp(elem->length, "ll")) == 0)
		elem->type = ULLONG_INT;
	if ((ft_strcmp(elem->length, "h")) == 0)
		elem->type = USHORT_INT;
	if ((ft_strcmp(elem->length, "hh")) == 0)
		elem->type = U_CHAR;
	if ((ft_strcmp(elem->length, "j")) == 0)
		elem->type = UINT_MAXT;
	if ((ft_strcmp(elem->length, "z")) == 0)
		elem->type = SIZE_T;
}

void	type_signed(t_lst *elem)
{
	elem->type = INT;
	if ((ft_strcmp(elem->length, "l")) == 0 || elem->sp == 'D')
	{
		elem->type = LONG_INT;
		return ;
	}
	if ((ft_strcmp(elem->length, "ll")) == 0)
		elem->type = LLONG_INT;
	if ((ft_strcmp(elem->length, "h")) == 0)
		elem->type = SHORT_INT;
	if ((ft_strcmp(elem->length, "hh")) == 0)
		elem->type = CHAR;
	if ((ft_strcmp(elem->length, "j")) == 0)
		elem->type = INT_MAXT;
	if ((ft_strcmp(elem->length, "z")) == 0)
		elem->type = SIZE_T;
}

void	what_type(t_lst *elem)
{
	if (elem->sp == '%')
		elem->type = PERCENT;
	if (elem->sp == 's' || elem->sp == 'S' || elem->sp == 'C')
	{
		if ((elem->sp != 'C' && elem->sp != 'S') &&
			ft_strcmp(elem->length, "l"))
			elem->type = ARG_STR;
		else
			elem->type = (elem->sp == 'C' ? WCHAR_T : WCHAR_TSTR);
	}
	if (elem->sp == 'c')
	{
		if (ft_strcmp(elem->length, "l"))
			elem->type = INT;
		else
			elem->type = WIN_T;
	}
	if (elem->sp == 'p')
		elem->type = VOID;
	if (elem->sp == 'd' || elem->sp == 'D' || elem->sp == 'i')
		type_signed(elem);
	if (elem->sp == 'u' || elem->sp == 'U' || elem->sp == 'o' || elem->sp
		== 'O' || elem->sp == 'x' || elem->sp == 'X')
		type_unsigned(elem);
}
