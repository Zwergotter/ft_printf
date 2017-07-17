/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 15:03:03 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/17 22:35:37 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
