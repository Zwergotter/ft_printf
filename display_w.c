/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 21:02:44 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/25 19:45:52 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	choosing_mask(char **tab, char *bin, char **tmp)
{
	int	len;
	int len_tab;

	len = ft_strlen(bin);
	if (len <= 7)
		*tmp = ft_strdup(tab[0]);
	if (len > 7 && len <= 11)
		*tmp = ft_strdup(tab[1]);
	if (len > 11 && len <= 16)
		*tmp = ft_strdup(tab[2]);
	if (len > 16)
		*tmp = ft_strdup(tab[3]);
	len -= 1;
	len_tab = ft_strlen(*tmp) - 1;
	while (len > -1 && len_tab > -1)
	{	
		if ((*tmp)[len_tab] == 'x')
			(*tmp)[len_tab] = bin[len--];
		len_tab--;
	}
}

char	*unicode_masks(char *bin)
{
	char *tab[4];
	char *tmp;
	int i;

	i = 0;
	tab[0] = "0xxxxxxx";
	tab[1] = "110xxxxx10xxxxxx";
	tab[2] = "1110xxxx10xxxxxx10xxxxxx";
	tab[3] = "11110xxx10xxxxxx10xxxxxx10xxxxxx";
	choosing_mask(tab, bin, &tmp);
	while (tmp[i])
	{
		if (tmp[i] == 'x')
			tmp[i] = '0';
		i++;
	}
	return (tmp);
}

//pour flags 0 et autres, sans doute a faire avec display_char avant et apres

void	display_wchar(va_list ap)
{
	unsigned long int	nb;
	char 				*bin;
	char 				*tmp;
	int 				i;

	i = 0;
	nb = va_arg(ap, wchar_t);
	bin = ft_itoa_base(nb, 2);
	if (ft_strlen(bin) <= 7)
		write(1, &nb, 1);
	else
	{
		tmp = unicode_masks(bin);
		while(tmp[i])
			{
				ft_putchar(ft_atoi_base(ft_strsub(tmp, i, 8), 2));
				i += 8;
			}
	}
}
