/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 16:27:03 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/05 16:27:08 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Displays message according to the error and then exits.
*/

#include "ft_printf.h"

void	error_displayed(t_error error)
{
	if (error == ARGUMENT)
		ft_putstr_fd("Argument is not valid\n", 2);
	if (error == MALLOC)
		ft_putstr_fd("Memory allocation failed\n", 2);
	exit(0);
}
