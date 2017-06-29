/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:29:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/29 17:14:40 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
differentes choses a gerer encore: que se passe t il avec %%? autre string a faire ou non? 
Que se passe t il si j'essaie de creer une chaine vide?
QUE SE PASSE T IL SI ERREUR PARSING/CHECKING
*/


/*
** File to check all elements which begin by % one by one
** Apparently strings written juste after a specifier, even without a white space, are fine.
** But need to check stuff like "%wwwwwd" that can't be acceptable
*/

int filling_length(t_lst *elem, int i)
{
	int j;

	j = 0;
	elem->length[j++] = elem->arg[i++];
	if ((elem->arg[i - 1] == 'h' || elem->arg[i - 1] == 'l') && elem->arg[i - 1] == elem->arg[i])
		elem->length[j++] = elem->arg[i++];
	while (j < 3)
		elem->length[j++] = '\0';
	return (i);
}

int option_found(t_lst *elem, int i)
{
	if ((elem->arg[i] != '0' && ft_isdigit(elem->arg[i] + 0) && !elem->i_pre)
		|| (is_precision(elem->arg[i], elem)))
	{
		i += (is_precision(elem->arg[i], elem) ? 1 : 0);
		while (is_flag(elem->arg[i], elem))
			i++;
		if (elem->pre == '.')
			elem->i_pre = ft_atoi(&elem->arg[i]);
		else
			elem->width = ft_atoi(&elem->arg[i]);
		while (i < elem->len - 2 && ft_isdigit(elem->arg[i] + 0))
			i++;
		if (!is_precision(elem->arg[i], elem) && !(is_specifier(elem->arg[i])))
			i++;
	}
	i += (is_flag(elem->arg[i], elem) ? 1 : 0);
	if (is_length(elem->arg[i]))
		i = filling_length(elem, i);
	return (i);
}

void substring(t_lst *elem, int i)
{
	char *str;

	str = elem->arg;
	elem->arg = ft_strsub(str, i, elem->len - i);
	elem->type = STR;
	free(str);
}

/*
** Order a gerer, flag -> width -> precision -> length
** un ou plusieurs de ceux ci peuvent etre zappes mais l'ordre doit etre respecte
** GERER aussi le %%
*/

int checking(t_lst *elem)
{
	int i;

	i = (is_flag(elem->arg[1], elem) ? 2 : 1);
	while (i < elem->len - 1 && everything_at_once(elem->arg[i], elem))
		i = option_found(elem, i);
	if (is_specifier(elem->arg[i]))
	{
		elem->spe = elem->arg[i];
		what_type(elem);
	}
	else
	{
		if (i >= elem->len - 1)
			return (0);// rien a afficher?
		else
			substring(elem, i);
	}
	return (1);
}

/*
** Checking one by one each element
*/

void check_elem(t_lst **first)
{
	t_lst *tmp;

	tmp = *first;
	while (tmp)
	{
		if (tmp->type != STR)
		{
			if (!checking(tmp))
				tmp->type = EMPTY;
		}
		tmp = tmp->next;
	}
}
