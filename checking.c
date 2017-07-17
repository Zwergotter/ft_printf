/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:29:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/17 17:47:48 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
** Will specify length found in string and then return the index after this
*/

int		filling_length(t_lst *elem, int i)
{
	int j;

	j = 0;
	elem->length[j++] = elem->arg[i++];
	if ((elem->arg[i - 1] == 'h' || elem->arg[i - 1] == 'l') &&
		elem->arg[i - 1] == elem->arg[i])
		elem->length[j++] = elem->arg[i++];
	while (j < 3)
		elem->length[j++] = '\0';
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
			{
				elem->i_pre = ft_atoi(&elem->arg[i]);
				// ft_putstr(CYN"\nIn opt found in elem pre, i is : ");
				// ft_putnbr(i);
			}
		else
			elem->width = ft_atoi(&elem->arg[i]);
		while (i < elem->len - 2 && ft_isdigit(elem->arg[i] + 0))
			{
				i++;
				// ft_putstr(CYN"\nIn opt found in while, i is : ");
				// ft_putnbr(i);
			}
		if (elem->arg[i] == '+')
			elem->sign = elem->arg[i++];
		if (!is_precision(elem->arg[i], elem) && !(is_specifier(elem->arg[i])))
			{
				i++;
				// ft_putstr(CYN"\nIn opt found in last if, i is : ");
				// ft_putnbr(i);
			}
	}
	i += (is_flag(elem->arg[i], elem) ? 1 : 0);
	if (is_length(elem->arg[i]))
	{
		if (!elem->length[0])
			i = filling_length(elem, i);
		else
		{
			elem->length[0] = 'z';
			elem->length[1] = '\0';
			i++;
		}
	}
	return (i);
}

void	substring(t_lst *elem, int i)
{
	char *str;

	str = elem->arg;
	elem->arg = ft_strsub(str, i, elem->len - i);
	free(str);
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
	// ft_putstr(GRN"\nIn checking at the beginning, i is : ");
	// ft_putnbr(i);
	if (i > elem->len)
		return (0);
	while (i < elem->len && everything_at_once(elem->arg[i], elem))
		{
			// ft_putstr(GRN"\nIn checking in while, i is : ");
			// ft_putnbr(i);
			i = option_found(elem, i);
			// ft_putstr(GRN"\nIn checking in while, after option found i is : ");
			// ft_putnbr(i);
		}
	if (is_specifier(elem->arg[elem->len - 1]))
	{
		elem->spe = elem->arg[i];
		what_type(elem);
	}
	else
	{
		if (i <= elem->len)
			{
				if (elem->pre && !elem->i_pre)
					i--;
				substring(elem, i);
				// ft_putstr(MAG"\n\nAfter substring, i is : ");
				// ft_putnbr(i);
				// ft_putstr(YEL" -  And substr is ");
				// ft_putstr(elem->arg);
			}
		else
		{
			if (elem->width && elem->next)
				elem->width -= elem->width - (ft_strlen(elem->next->arg) + 1);/////?????????????????????
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
			ft_putstr(BLU"\nAfter checking elem");
			ft_putstr("\narg str is : -");
			ft_putstr(tmp->arg);
			ft_putstr("-\n");
		}
		tmp = tmp->next;
		i++;
	}
}
