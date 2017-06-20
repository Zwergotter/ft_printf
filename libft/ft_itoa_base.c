/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:01:50 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/21 00:02:30 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(uintmax_t number, int base)
{
	int			i;
	uintmax_t	save;
	char		*str;
	char		*result;

	i = 0;
	if (number == 0)
		i++;
	save = number;
	while (number > 0 && ++i)
		number = number / base;
	str = "0123456789abcdef";
	if (!(result = malloc(i + 1)))
		exit (0);
	result[i] = '\0';
	result[0] = '-';
	while (i && i--)
	{
		result[i] = str[save % base];
		save = save / base;
	}
	return (result); 
}
