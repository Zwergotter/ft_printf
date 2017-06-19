/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:48:22 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/19 17:01:23 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Will write a character i times.
*/

void write_char(char c, int i)
{
	while (i-- > 0)
		write(1, &c, 1);
}

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
	if (list->type == LONG_INT || list->type == U_INT || list->type == SHORT_INT
		|| list->type == USHORT_INT || list->type == ULLONG_INT ||
		list->type == INT || list->type == LLONG_INT || list->type == ULONG_INT
		|| list->type == SIZE_T || list->type == INT_MAXT ||
		list->type == UINT_MAXT || list->type == CHAR || list->type == U_CHAR)
	{
		if (list->spe != 'c')
			display_number(list, ap, elem);
		else
			display_char(list, va_arg(ap, int));
	}
	if (list->type == ARG_STR)
		display_str(list, ap, elem);
	if (list->type == PERCENT)
		display_char(list, '%');
	free(elem);
}
