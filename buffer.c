/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 15:03:03 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/28 18:05:29 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char  *bufferize(char **saved, char buf, int nb)
{
	char		*tmp;
	char 		tmp2[2];
	int			i;

	tmp = *saved;
	tmp2[0] = buf;
	tmp2[1] = '\0';
	i = 0;
	if (tmp)
	{
		while (i++ < nb)
			*saved = ft_strjoin(*saved, tmp2);
		free(tmp);
	}
	else
		*saved = ft_strdup(tmp2);
	return (*saved);
}
