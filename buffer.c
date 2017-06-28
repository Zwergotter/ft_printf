/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 15:03:03 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/28 22:47:52 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char  *bufferize_str(char **saved, char *str, t_lst *list)
{
	if (*saved)
		*saved = ft_strjoinfree(*saved, str, 1);
	else
		*saved = ft_strdup(str);
	list->nb += ft_strlen(str);
	return (*saved);
}

char  *bufferize_c(char **saved, char c, int nb, t_lst *list)
{
	char 		tmp2[2];
	int			i;

	tmp2[0] = c;
	tmp2[1] = '\0';
	i = 0;
	if (*saved)
	{
		while (i++ < nb)
			*saved = ft_strjoinfree(*saved, tmp2, 1);
	}
	else
		*saved = ft_strdup(tmp2);
	list->nb += nb;
	return (*saved);
}

// int		ft_nputc(char c, int j)
// {
// 	static char *buf = ft_strdup("");
// 	static int i = 0;
// 	char *tmp;

// 	++i;
	// if ((tmp = malloc(i + 1)) == NULL)
	// 	exit(0);
// 	tmp[0] = 0;
// 	strcat(tmp, buf);
// 	tmp[i - 1] = c;
// 	tmp[i] = 0;
// 	free(buf);
// 	buf = tmp;
// 	if (j = -1)
// 	{
// 		write(1, buf, i);
// 		return (i);
// 	}
// }
