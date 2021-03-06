/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:29:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 19:00:26 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Checking all at once and applying corresponding function as well
*/

int		everything_at_once(char c, t_lst *elem)
{
	if (ft_isdigit(c + 0) || is_precision(c, elem) || is_length(c) ||
		is_flag(c, elem))
		return (1);
	return (0);
}

/*
** Will specify length found in string and then return the index after this
*/

int		filling_length(t_lst *elem, int i)
{
	int j;

	j = 0;
	if (!elem->length[0])
	{
		elem->length[j++] = elem->arg[i++];
		if ((elem->arg[i - 1] == 'h' || elem->arg[i - 1] == 'l') &&
			elem->arg[i - 1] == elem->arg[i])
			elem->length[j++] = elem->arg[i++];
		while (j < 3)
			elem->length[j++] = '\0';
	}
	else
	{
		elem->length[0] = 'z';
		elem->length[1] = '\0';
		i++;
	}
	return (i);
}

/*
** Finding all options in string between a percent and a specifier if there's
** one and putting them in list's element specifing for what kind of option
** Returns the index
*/

int		option_found(t_lst *elem, int i)
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
		if (elem->arg[i] == '+')
			elem->sign = elem->arg[i++];
		if (!is_precision(elem->arg[i], elem) && !(is_specifier(elem->arg[i])))
			i++;
	}
	i += (is_flag(elem->arg[i], elem) ? 1 : 0);
	if (is_length(elem->arg[i]))
		i = filling_length(elem, i);
	return (i);
}

/*
** Checking at first if flag is just after % or not
** If it is, it's starting itn starts at 2 and if not at 1
** Then it will call option_found until something isn't an option
** or we reach second to last character
** If last character is a specifier, it will give a type thanks to
** what_type.
** If not, the format isn't valid and either it will do nothing or
** will save the substring without percent.
*/

int		checking(t_lst *elem)
{
	int i;

	i = (is_flag(elem->arg[0], elem) ? 1 : 0);
	if (i > elem->len)
		return (0);
	while (i < elem->len && everything_at_once(elem->arg[i], elem))
		i = option_found(elem, i);
	if (is_specifier(elem->arg[elem->len - 1]))
	{
		elem->sp = elem->arg[i];
		what_type(elem);
	}
	else
	{
		if (i <= elem->len)
			substring(elem, ((elem->pre && !elem->i_pre) ? i - 1 : i));
		else
		{
			if (elem->width && elem->next)
				elem->width -= elem->width - (ft_strlen(elem->next->arg) + 1);
		}
	}
	return (1);
}

/*
** Checking one by one each element and sending them to checking function
*/

void	check_elem(t_lst **first)
{
	t_lst	*tmp;
	int		i;

	tmp = *first;
	i = 1;
	while (tmp)
	{
		if (tmp->type != STR)
		{
			if (!checking(tmp))
				tmp->type = EMPTY;
		}
		tmp = tmp->next;
		i++;
	}
}
