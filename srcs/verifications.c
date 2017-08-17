/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 22:40:53 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 15:27:52 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Checks if a character is a flag, a digit for precision or width, or length
*/

int	everything(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0' || c == '.'
		|| c == 'h' || c == 'l' || c == 'j' || c == 'z' || ft_isdigit(c + 0))
		return (1);
	return (0);
}

/*
** Function to identify a specifier when encounter
*/

int	is_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||
			c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X'
			|| c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

/*
** Functions to identify flag, precision and length
*/

int	is_flag(char c, t_lst *elem)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
	{
		if (c == '0' && elem->flag != '-')
		{
			elem->zero = 1;
			return (1);
		}
		if (c == '#')
		{
			elem->hash = '#';
			return (1);
		}
		if (elem->flag == ' ' || !elem->flag)
		{
			elem->flag = c;
			return (1);
		}
		if (c == '+')
			elem->sign = c;
		return (1);
	}
	return (0);
}

int	is_precision(char c, t_lst *elem)
{
	if (c == '.')
	{
		elem->pre = '.';
		return (1);
	}
	return (0);
}

int	is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}
