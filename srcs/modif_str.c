/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:59:58 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 15:27:41 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	substring(t_lst *elem, int i)
{
	char *str;

	str = elem->arg;
	elem->arg = ft_strsub(str, i, elem->len - i);
	free(str);
}

void	upper_string(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
}
