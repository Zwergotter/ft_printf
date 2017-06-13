/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:48:22 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/13 16:41:11 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
** Will write a character i times.
*/

void write_char(char c, int i)
{
	while (i-- > 0)
		write(1, &c, 1);
}

/*
** Function that will call the appropriate one in order to format and then
** display arguments one by one and according to their types
*/

void	displaying(t_lst *list, va_list ap)
{
	t_error	error;
	t_one	*elem;

	error = MALLOC;
	if ((elem = (t_one*)malloc(sizeof(t_one))) == NULL)
		error_displayed(error);
	ft_bzero(elem, (sizeof(t_one)));
	if (list->type == INT)
	{
		if (list->spe != 'c')
			display_int(list, ap, elem);
		else
			display_char(list, ap);
	}
	if (list->type == ARG_STR)
		display_str(list, ap, elem);
	free(elem);
}
