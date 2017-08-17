/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:48:22 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/13 18:08:31 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		is_numeric(t_type type)
{
	if (type == LONG_INT || type == U_INT || type == SHORT_INT || type == INT ||
		type == USHORT_INT || type == ULLONG_INT || type == LLONG_INT ||
		type == ULONG_INT || type == SIZE_T || type == INT_MAXT || type == VOID
		|| type == UINT_MAXT || type == CHAR || type == U_CHAR)
		return (1);
	return (0);
}

void	init_one(t_one *one)
{
	one->wstr = NULL;
	one->str = NULL;
	one->oth = NULL;
	one->hash = NULL;
	one->len = 0;
	one->sign = 0;
	one->c = 0;
	one->pre = 0;
	one->width = 0;
	one->signed_nb = 0;
}

void	free_one(t_one *one)
{
	free(one->str);
	free(one->hash);
	free(one->oth);
	free(one);
}

/*
** Function that will call the appropriate one in order to format and then
** display arguments one by one and according to their types.
** Initialize an element of list t_one and will free it at the end.
*/

void	displaying(t_lst *list, va_list ap)
{
	t_one	*elem;

	if ((elem = (t_one*)malloc(sizeof(t_one))) == NULL)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(0);
	}
	init_one(elem);
	if (is_numeric(list->type))
	{
		if (list->sp != 'c')
			display_number(list, ap, elem);
		else
			display_char(list, va_arg(ap, int));
	}
	if (list->type == WCHAR_T || list->type == WIN_T)
		display_wchar(va_arg(ap, wchar_t), list);
	if (list->type == WCHAR_TSTR)
		display_wstr(ap, list);
	if (list->type == PERCENT)
		display_char(list, '%');
	if (list->type == ARG_STR)
		display_str(list, ap, elem);
	free_one(elem);
}
