/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosi <cosi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:54:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 02:56:55 by cosi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	string_valid(t_lst *list, t_one *one)
{
	if (one->width > 0)
	{
		if (list->flag == '-')
		{
			if (one->oth)
				write_str(one->oth);
			write_c(' ', one->width);
		}
		else
		{
			list->zero && list->flag != '-' ?
				write_c('0', one->width) :
				write_c(' ', one->width);
			if (one->oth)
				write_str(one->oth);
		}
	}
	else
	{
		if (one->oth)
			write_str(one->oth);
	}
}

void	new_string(t_lst *list, t_one *one, char *str)
{
	one->str = ft_strdup(str);
	one->oth = (list->i_pre && list->i_pre < (int)ft_strlen(one->str) ?
		ft_strsub(one->str, 0, list->i_pre) : ft_strdup(one->str));
	one->len = ft_strlen(one->oth);
}

void	display_str(t_lst *list, va_list ap, t_one *one)
{
	char *str;

	str = va_arg(ap, char*);
	if (!str)
	{
		if (!list->width)
		{
			write_str("(null)");
			return ;
		}
	}
	if (str)
		new_string(list, one, str);
	one->width = list->width - (one->len ? one->len : 0);
	if (list->pre && !list->i_pre)
	{
		if (list->width)
			list->zero && list->flag != '-' ?
				write_c('0', list->width) :
				write_c(' ', list->width);
	}
	else
		string_valid(list, one);
}

void	display_char(t_lst *list, int nb)
{
	char fill;
	char c;

	c = nb - 0;
	fill = list->zero && list->flag != '-' ? '0' : ' ';
	if (list->flag != '#')
	{
		if (list->width && list->flag != '-')
			write_c(fill, list->width - 1);
		write_c(nb, 1);
		if (list->width && list->flag == '-')
			write_c(fill, list->width - 1);
	}
	else
		return ;
}
