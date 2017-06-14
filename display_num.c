/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:41:21 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/14 17:10:14 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*unsigned_long_itoa(unsigned long long n)
{
	size_t		len;
	int 		i;
	char		*new;

	len = ft_countdigits(n);
	i = 0;
	if (!(new = ft_strnew(len)))
		return (NULL);
	if (n == 0)
		return (ft_strdup("0"));
	new[len] = '\0';
	while (n > 9)
	{
		new[--len] = ((n % 10) + '0');
		n = n / 10;
	}
	new[i] = (n + '0');
	return (new);
}

char		*long_itoa(intmax_t n)
{
	size_t		len;
	int			i;
	char		*new;

	len = ft_countdigits(n);
	i = 0;
	if (!(new = ft_strnew(len)))
		return (NULL);
	
	if (n == 0 || n == ~0LL)
		return (n == 0 ? ft_strdup("0") : ft_strdup("-9223372036854775808"));
	if (n < 0)
	{
		n = -n;
		new[i++] = '-';
	}
	new[len] = '\0';
	while (n > 9)
	{
		new[--len] = ((n % 10) + '0');
		n = n / 10;
	}
	new[i] = (n + '0');
	return (new);
}

void minus_flag(t_lst *list, t_one *one)
{
	// if (list->type == INT && one->sign == '-')
	if (one->sign == '-')
	{
		write(1, &one->sign, 1);
		list->nb += 1;
		one->diff_width--;
	}
	if (one->diff_pre > 0)
	{
		while (one->diff_pre-- > 0)
		{
			write(1, "0",  1);
			list->nb += 1;
		}
	}
	ft_putstr(one->new);
	while (one->diff_width-- > 0)
	{
		write(1, &one->c,  1);
		list->nb += 1;
	}
}

void other_flags(t_lst *list, t_one *one)
{
	if ((list->flag == ' ' && list->type == ARG_STR) || (list->flag == ' ' &&
		one->str[0] != '-' && (list->pre == '.' || list->width < one->len)))
	{
		write(1, " ", 1);
		list->nb += 1;
	}
	while (one->diff_width-- > 0)
	{
		write(1, &one->c,  1);
		list->nb += 1;
	}
	// if (list->type == INT && (list->flag == '+'|| one->sign == '-'))
	if (list->flag == '+'|| one->sign == '-')
	{
		write(1, &one->sign, 1);
		list->nb += 1;
		one->diff_width--;
	}
	while (one->diff_pre-- > 0)
	{
		write(1, "0",  1);
		list->nb += 1;
	}
	ft_putstr(one->new);
}

void 	what_kind(t_lst *list, va_list ap, t_one *one)
{
	if (list->type == INT)
		one->str = long_itoa((va_arg(ap, int)));
	if (list->type == U_INT)
		one->str = long_itoa((va_arg(ap, unsigned int)));
	if (list->type == SHORT_INT)
		one->str = long_itoa((short)(va_arg(ap, int)));
	if (list->type == USHORT_INT)
		one->str = long_itoa((unsigned short)(va_arg(ap, int)));
	if (list->type == LONG_INT)
		one->str = long_itoa((va_arg(ap, long)));
	if (list->type == ULONG_INT)
		one->str = long_itoa((va_arg(ap, unsigned long)));
	if (list->type == LLONG_INT)
		one->str = long_itoa(va_arg(ap, long long));
	if (list->type == ULLONG_INT)
		one->str = unsigned_long_itoa(va_arg(ap, unsigned long long));
}

void	display_number(t_lst *list, va_list ap, t_one *one)
{
	what_kind(list, ap, one);
	one->len = ft_strlen(one->str);
	one->sign = (one->str[0] == '-' ? '-' : '+');
	one->new = (one->sign == '-' ? ft_strsub(one->str, 1, one->len - 1) : one->str);
	if (list->i_pre && list->i_pre > one->len) // quelle est l'influence de la precision sur les autres types (est ce quíl y a une influence par ex avec one->string??)
		one->diff_pre = list->i_pre - one->len;
	if (list->width > list->i_pre && list->width > one->len)
		one->diff_width = list->width - (one->diff_pre + one->len)  - (one->str[0] == '-' || list->flag == ' ' || list->flag == '+' ? 1 : 0);
	one->c = (list->flag == '0' && !list->pre ? '0' : ' ');
	if (list->flag == '-')
		minus_flag(list, one);
	else
		other_flags(list, one);
	list->nb = list->nb + ft_strlen(one->new);
}
