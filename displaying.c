/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaying.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:48:22 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/13 16:41:11 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

// toute mettre dans une chaine et non pas affichage au fur et a mesure???
// signe a une influence sur width(la longueur) mais pas sur precision
// si precision > length -> nb zeros a ecrire = precision - length (- 1 si signe ou si flag espace existe)
// si width > precision -> nb d'espaces a ecrire = width - (precision > length ? precision ; length)  -- signe et flag espace ne changent pas ce nombre(ne lui enleve pas un charactere, un 0, a afficher). il faut donc les rajouter en plus

void write_char(char c, int i)
{
	while (i-- > 0)
		write(1, &c, 1);
}

void	displaying(t_lst *list, va_list ap)
{
	t_error	error;
	t_one	*elem;

	error = MALLOC;
	if ((elem = (t_one*)malloc(sizeof(t_one))) == NULL)
		error_displayed(error);
	ft_bzero(elem, (sizeof(t_one)));
	if (list->type == INT)
	{
		if (list->spe != 'c')
			display_int(list, ap, elem);
		else
			display_char(list, ap);
	}
	if (list->type == ARG_STR)
		display_str(list, ap, elem);
	free(elem);
}
