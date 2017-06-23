/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 21:02:44 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/23 22:29:53 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>


void display_wchar(t_lst *list, va_list ap)
{
	unsigned int nb;

	printf(RED"IN DISPLAY WCHAR\n"RESET);
	nb = va_arg(ap, wchar_t);
	char fill;

	fill = (list->flag == '0' ? '0' : ' ');
	if (list->flag != '#')
	{
		if (list->width && list->flag != '-')
			write_char(fill, list->width - 1);
		if (list->width && list->flag == '-')
			write_char(fill, list->width - 1);
	}
	printf("wchar_t value is %u\n", nb);
}
