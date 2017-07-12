/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 17:44:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/12 14:35:59 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_unsigned(t_lst *elem)
{
	elem->type = U_INT;
	if ((ft_strcmp(elem->length, "l")) == 0 || elem->spe == 'U')
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
	if ((ft_strcmp(elem->length, "l")) == 0 || elem->spe == 'D')
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
	if (elem->spe == '%')
		elem->type = PERCENT;
	if (elem->spe == 's' || elem->spe == 'S' || elem->spe == 'C')
	{
		if ((elem->spe != 'C' && elem->spe != 'S') &&
			ft_strcmp(elem->length, "l"))
			elem->type = ARG_STR;
		else
			elem->type = (elem->spe == 'C' ? WCHAR_T : WCHAR_TSTR);
	}
	if (elem->spe == 'c')
	{
		if (ft_strcmp(elem->length, "l"))
			elem->type = INT;
		else
			elem->type = WIN_T;
	}
	if (elem->spe == 'p')
		elem->type = VOID;
	if (elem->spe == 'd' || elem->spe == 'D' || elem->spe == 'i')
		type_signed(elem);
	if (elem->spe == 'u' || elem->spe == 'U' || elem->spe == 'o' || elem->spe
		== 'O' || elem->spe == 'x' || elem->spe == 'X')
		type_unsigned(elem);
}
