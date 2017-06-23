/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 17:44:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/23 22:01:55 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_unsigned(t_lst *elem)
{
	elem->type = U_INT;
	if ((ft_strcmp(elem->length, "l")) == 0)
		elem->type = ULONG_INT;
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
	if ((ft_strcmp(elem->length, "l")) == 0)
		elem->type = LONG_INT;
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
		if (ft_strcmp(elem->length, "l"))
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
