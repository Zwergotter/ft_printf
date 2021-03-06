/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 15:03:03 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/13 18:23:14 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Creates a buffer in order to put all arguments read in it and then write
** only at the end of printf this buffer.
** Will either write this one if the int passed as argument is negative,
** meaning that there's a mistake with wchar or printf reaches its end and
** returns the result.
** Or will add the argument we've formated, thansk to %, at the buffer's end.
*/

int		ft_nputc(char *str, int j)
{
	static char	*buf = NULL;
	static int	i = 0;
	char		*tmp;
	int			result;

	if (buf == NULL)
		buf = ft_strdup("");
	if (j < 0)
	{
		if (j != -2)
			write(1, buf, i);
		*buf = 0;
		result = i;
		i = 0;
		return (result);
	}
	if ((tmp = malloc(i + j + 1)) == NULL)
		exit(0);
	*tmp = 0;
	ft_memcpy(tmp, buf, i + 1);
	ft_memcpy(tmp + i, str, j);
	i += j;
	free(buf);
	buf = tmp;
	return (0);
}

void	write_str(char *str)
{
	if (!str)
		return ;
	ft_nputc(str, ft_strlen(str));
}

void	write_c(char c, int nb)
{
	char	str[nb + 1];
	int		i;

	i = nb;
	str[nb] = 0;
	while (nb--)
		str[nb] = c;
	ft_nputc(str, i);
}
