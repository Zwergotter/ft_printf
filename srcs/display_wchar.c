/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_wchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 21:02:44 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 17:06:28 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Will create a temporary string that is the bin value put in corresponding
** unicode masks.
** Then it calls write_c until, octet by octet.
*/

void		writing_wchar(char *bin)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = unicode_masks(bin);
	while (tmp[i])
	{
		write_c(ft_atoi_base(ft_strsub(tmp, i, 8), 2), 1);
		i += 8;
	}
	free(tmp);
}

/*
** Converts long int as bin, string with binary value of nb
** Checks if macro MB_CUR_MAX is 1, then we can only write on max 1 octet, so if
** bin's length is more than 8 characters we willhave a mistake.
** If not it calls directly write_c
** Else it's calling writing_wchar
*/

void		display_wchar(unsigned long int nb, t_lst *list)
{
	char	*bin;

	bin = ft_itoa_base(nb, 2, 0);
	if (ft_strlen(bin) <= 7 || MB_CUR_MAX == 1)
	{
		if (ft_strlen(bin) > 7)
		{
			free(bin);
			list->nb = -1;
			return ;
		}
		write_c(nb, 1);
	}
	else
		writing_wchar(bin);
	free(bin);
}

void		writing_wstr(t_lst *list, int width, int pre, wchar_t *str)
{
	int		i;

	i = -1;
	if (list->flag != '-' && width > 0)
	{
		write_c(list->zero ? '0' : ' ', width);
		width = 0;
	}
	while (str[++i])
	{
		display_wchar(str[i], list);
		if (pre)
		{
			pre -= ft_wcharlen(str[i]);
			if (pre <= 0)
				break ;
		}
	}
	if (width > 0)
		write_c(' ', width);
}

int			counting_pre(t_lst *list, wchar_t *str)
{
	int		nb_char;
	int		i;

	i = 0;
	nb_char = 0;
	while (list->i_pre >= nb_char + ft_wcharlen(str[i]))
		nb_char += ft_wcharlen(str[i++]);
	return (nb_char);
}

void		display_wstr(va_list ap, t_lst *list)
{
	wchar_t	*str;
	int		pre;
	int		width;

	pre = list->i_pre;
	str = va_arg(ap, wchar_t*);
	if (!str || (list->pre && !list->i_pre))
	{
		if (!str)
			write_str("(null)");
		else
			write_c(list->zero ? '0' : ' ', list->width);
		return ;
	}
	if (list->width && list->i_pre >= list->width)
		width = 0;
	else
	{
		if (list->i_pre)
			pre = counting_pre(list, str);
		width = list->width - (list->i_pre ? pre : ft_wstrlen(str));
	}
	writing_wstr(list, width, pre, str);
}
