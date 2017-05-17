/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:29:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/05/15 19:18:08 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
differentes choses a gerer encore: que se passe t il avec %%? autre string a faire ou non? 
Que se passe t il si j'essaie de creer une chaine vide?
*/


/*
** File to check all elements which begin by % one by one
** Apparently strings written juste after a specifier, even without a white space, are fine.
** But need to check stuff like "%wwwwwd" that can't be acceptable
*/

#include "ft_printf.h"

int is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
		return (1);
	return (0);
}

/*
** Nombre avant . -> sont la taille. Sinon, c'est la precision.
*/

int is_precision(char c)
{
	if (c == '.')
		return (1);
	return (0);
}

/*
** ATTENTION. Aussi hh et ll a gerer.
*/
int is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return(0);
}

/*
** Checking all at once
*/

int everything_at_once(char c)
{
	if (ft_isdigit(c + 0) || is_precision(c) || is_length(c) || is_flag(c))
		return (1);
	return (0);
}

/*
** Order a gerer, flag -> width -> precision -> length
** un ou plusieurs de ceux ci peuvent etre zappes mais l'ordre doit etre respecte
** GERER aussi le %%
*/

int checking(t_lst *elem)
{
	int len;
	int i;
	int j;
	char *str;

	len = ft_strlen(elem->arg);
	if (len < 2)
		return (0); // rien a afficher?
	i = 1;
	if (is_flag(elem->arg[i]))
			elem->flag = elem->arg[i++];
	while (i < len - 1 && everything_at_once(elem->arg[i]))
	{
		if ((elem->arg[i] != '0' && ft_isdigit(elem->arg[i] + 0) && !elem->precision) || (is_precision(elem->arg[i])))
		{ //que se passe t il avec la precision s'il y a uniquement "."?"
			if (is_precision(elem->arg[i]))
				i++;
			j = i;
			while (i < len - 2 && ft_isdigit(elem->arg[i] + 0))
				i++;
			if (is_precision(elem->arg[j - 1]))
			{
				if (!ft_isdigit(elem->arg[i] + 0))
					elem->precision = 0;
				else
					elem->precision = ft_atoi(&elem->arg[j]);
			}
			else
				elem->width = ft_atoi(&elem->arg[j]);
			i++;
		}
		if (is_flag(elem->arg[i]))
			i++;
		if (is_length(elem->arg[i]))
		{
			j = 0;
			elem->length[j++] = elem->arg[i++];
			if ((elem->arg[i - 1] == 'h' || elem->arg[i - 1] == 'l') && elem->arg[i - 1] == elem->arg[i])
				elem->length[j++] = elem->arg[i++];
			while (j < 3)
				elem->length[j++] = '\0';
		}
	}
	if (is_specifier(elem->arg[i]))
	{
		elem->spe = elem->arg[i];
		what_type(elem);
	}
	else
	{
		if (i >= len - 1)
			return (0);
		else
		{
			str = elem->arg;
			elem->arg = ft_strsub(str, i, len - i);
			elem->type = STR;
			free(str);
		}
	}
	return (1);
}

void check_elem(t_lst **first)
{
	t_lst *tmp;
	t_error error;
	char *str;

	tmp = *first;
	error = ARGUMENT;
	while (tmp)
	{
		if (tmp->type != STR)
			if (!checking(tmp))
			{
				str = tmp->arg;
				tmp->type = STR;
				tmp->arg = NULL;
				free(str);
				error_displayed(error);
			}
		tmp = tmp->next;
	}
}
