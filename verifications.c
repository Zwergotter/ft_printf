/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 22:40:53 by edeveze           #+#    #+#             */
/*   Updated: 2017/05/27 22:51:02 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

/*
** Functions to identify a specifier.
*/

int	is_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p'
			|| c == 'd' || c == 'D' || c == 'i' ||
			c == 'o' || c == 'O' || c == 'u' ||
			c == 'U' || c == 'x' || c == 'X' ||
			c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

int	is_flag(char c, t_lst *elem)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
	{
		elem->flag = c;
		return (1);
	}
	return (0);
}

/*
** Nombre avant . -> sont la taille. Sinon, c'est la precision.
*/

int	is_precision(char c, t_lst *elem)
{
	if (c == '.')
	{
		elem->pre = '.';
		return (1);
	}
	return (0);
}

/*
** ATTENTION. Aussi hh et ll a gerer.
*/
int	is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return(0);
}

/*
** Checking all at once
*/

int everything_at_once(char c, t_lst *elem)
{
	if (ft_isdigit(c + 0) || is_precision(c, elem) || is_length(c) ||
		is_flag(c, elem))
		return (1);
	return (0);
}