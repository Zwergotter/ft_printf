/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_w.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@marvin42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 21:02:44 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/26 18:15:26 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void	display_wchar(unsigned long int nb)
{
	char 				*bin;
	char 				*tmp;
	int 				i;

	i = 0;
	bin = ft_itoa_base(nb, 2);
	if (ft_strlen(bin) <= 7)
		write(1, &nb, 1);
	else
	{
		tmp = unicode_masks(bin);
		while (tmp[i])
			{
				ft_putchar(ft_atoi_base(ft_strsub(tmp, i, 8), 2));
				i += 8;
			}
		free (tmp);
	}
}

wchar_t		*ft_wstrdup(wchar_t *str)
{
	size_t	len;
	int		i;
	wchar_t	*dest;

	len = 0;
	while (str[len])
		len++;
	i = 0;
	dest = (wchar_t*)malloc(sizeof(*dest) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	display_wstr(va_list ap)
{
	wchar_t	*str;
	int		i;

	i = 0;
	str = ft_wstrdup(va_arg(ap, wchar_t*));
	while (str[i])
		display_wchar(str[i++]);
}
