/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 17:59:45 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	free_list(t_lst *list)
{
	t_lst	*s;

	while (list)
	{
		s = list->next;
		free(list->arg);
		free(list);
		list = s;
	}
}

/*
** Switches to next element of a list and destroys the previous one
*/

t_lst	*destroy_elem(t_lst *elem)
{
	t_lst *tmp;

	tmp = elem;
	elem = elem->next;
	free(tmp->arg);
	free(tmp);
	return (elem);
}

/*
** This function is called when in printf we encounter a string or an invalid
** format which will be interpert as a string on its own, no argument string.
** This kind can still have flags like 0 or - and it must display these as well
*/

void	only_string(t_lst *list)
{
	int len;

	len = ft_strlen(list->arg);
	if (list->type == NOARG_STR && list->width && list->flag != '-')
	{
		write_c(list->zero ? '0' : ' ', list->width - len);
		list->width = 0;
	}
	write_str(list->arg);
	if (list->type == NOARG_STR && list->width)
		write_c(' ', list->width - len);
}

/*
** Ft_printf will first parse all strings and conversion's formats in a list
** where each element is known as one kind or the other.
** Then it calls check_elem to save all information such as length, flags etc.
** And finally it's calling one by one each element and, if necessary, in
** displaying, the argument.
** Finally returns all number of characters read.
*/

int		ft_printf(char const *test, ...)
{
	va_list	ap;
	t_lst	*list;

	list = parsing(test);
	check_elem(&list);
	va_start(ap, test);
	while (list && list->type != EMPTY)
	{
		if (list->type == STR || list->type == NOARG_STR)
			only_string(list);
		else
			displaying(list, ap);
		if (list->nb == -1)
		{
			free_list(list);
			va_end(ap);
			return (ft_nputc(0, -2));
		}
		list = destroy_elem(list);
	}
	free_list(list);
	va_end(ap);
	return (ft_nputc(0, -1));
}
