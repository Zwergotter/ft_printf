/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosi <cosi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 03:27:55 by cosi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	free_list(t_lst *l)
{
	t_lst	*s;

	while (l)
	{
		s = l->next;
		free(l->arg);
		free(l);
		l = s;
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

void	only_string(t_lst *arg)
{
	int len;

	len = ft_strlen(arg->arg);
	if (arg->type == NOARG_STR && arg->width && arg->flag != '-')
	{
		write_c(arg->zero ? '0' : ' ', arg->width - len);
		arg->width = 0;
	}
	write_str(arg->arg);
	if (arg->type == NOARG_STR && arg->width)
		write_c(' ', arg->width - len);
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
	t_lst	*arg;

	arg = parsing(test);
	check_elem(&arg);
	va_start(ap, test);
	while (arg && arg->type != EMPTY)
	{
		if (arg->type == STR || arg->type == NOARG_STR)
			only_string(arg);
		else
			displaying(arg, ap);
		if (arg->nb == -1)
		{
			free_list(arg);
			va_end(ap);
			return (ft_nputc(0, -2));
		}
		arg = destroy_elem(arg);
	}
	free_list(arg);
	va_end(ap);
	return (ft_nputc(0, -1));
}
