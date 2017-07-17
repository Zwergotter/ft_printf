/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 21:28:16 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/17 21:34:27 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*upper_string(char *str)
{
	int		i;
	char	*new;

	new = ft_memalloc(ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			new[i] = str[i] - 32;
		else
			new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	substring(t_lst *elem, int i)
{
	char *str;

	str = elem->arg;
	elem->arg = ft_strsub(str, i, elem->len - i);
	free(str);
}