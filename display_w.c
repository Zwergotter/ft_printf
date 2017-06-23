/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 21:02:44 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/23 23:15:40 by edeveze          ###   ########.fr       */
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

void unicode_masks(char *bin, int len)
{
	char *tab[3];
	char *tmp;

	tab[0] = "0xxxxxxx";
	tab[1] = "110xxxxx10xxxxxx";
	tab[2] = "1110xxxx10xxxxxx10xxxxxx";
	tab[3] = "11110xxx10xxxxxx10xxxxxx10xxxxxx";
}

//pour flags 0 et autres, sans doute a faire avec display_char avant et apres

void display_wchar(va_list ap)
{
	unsigned long int nb;
	char *bin;
	int len;

	printf(RED"IN DISPLAY WCHAR\n"RESET);
	nb = va_arg(ap, wchar_t);
	bin = convert_binary(nb);
	len = ft_strlen(bin);
	if (len <= 7)
		write(1, &nb, 1);
	else
		unicode_masks(bin, len);
	printf("wchar_t value is %lu binary value is %s and length is %d\n", nb, bin, len);
}
