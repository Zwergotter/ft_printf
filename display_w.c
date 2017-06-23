/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 21:02:44 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/23 22:56:09 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char *convert_binary(unsigned long int nb)
{
	char					*ret;
	int						i;
	unsigned long int		tmp;

	tmp = nb;
	i = 0;
	while (tmp >= 2)
	{
		tmp = tmp / 2;
		i++;
	}
	ret = (char *)malloc(sizeof(char) * i + 1);
	if (ret)
	{
		ret[i + 1] = '\0';
		while (i >= 0)
		{
			tmp = nb % 2;
			ret[i] = 48 + tmp;
			nb = nb / 2;
			i--;
		}
	}
	return (ret);
}

void display_wchar(t_lst *list, va_list ap)
{
	unsigned long int nb;
	char *bin;
	int len;
	char fill;

	printf(RED"IN DISPLAY WCHAR\n"RESET);
	nb = va_arg(ap, wchar_t);
	bin = convert_binary(nb);
	len = ft_strlen(bin);
	fill = (list->flag == '0' ? '0' : ' ');
	if (list->flag != '#')
	{
		if (list->width && list->flag != '-')
			write_char(fill, list->width - 1);
		if (list->width && list->flag == '-')
			write_char(fill, list->width - 1);
	}
	printf("wchar_t value is %lu and binary value is %s\n", nb, bin);
}
