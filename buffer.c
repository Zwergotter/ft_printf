/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 15:03:03 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/27 16:49:34 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char  *bufferize(char **saved, char *buf, int nb)
{
	char		*tmp;
	int			i;

	tmp = *saved;
	i = 0;
	if (tmp)
	{
		while (i++ < nb)
			*saved = ft_strjoin(*saved, buf);
		free(tmp);
	}
	else
		*saved = ft_strdup(buf);
	return (*saved);
}
