/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 15:03:03 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/01 21:06:05 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	upper_string(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
}

void	write_str(char *str, t_lst *list)
{
	ft_putstr(str);
	list->nb += ft_strlen(str);
}

void	write_c(char c, int nb, t_lst *list)
{
	int	i;

	i = 0;
	while (i++ < nb)
		ft_putchar(c);
	list->nb += nb;
}
