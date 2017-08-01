/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/01 20:13:03 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>

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

t_lst *destroy_elem(t_lst *elem)
{
	t_lst *tmp;

	tmp = elem;
	elem = elem->next;
	free(tmp->arg);
	free(tmp);
	return (elem);
}

/*
** Attention a l'unicode
** attention aussi a comment on doit gerer l'int renvye quand il y a un \n
*/

void	only_string(t_lst *arg)
{
	int len;

	len = ft_strlen(arg->arg);
	if (arg->type == NOARG_STR && arg->width && arg->flag != '-')
	{
		(arg->zero == '0' ? write_c('0', arg->width - len, arg) :
			write_c(' ', arg->width - len, arg));
		arg->width = 0;
	}
	write_str(arg->arg, arg);
	if (arg->type == NOARG_STR && arg->width)
		write_c(' ', arg->width - len, arg);
}

/*
** Attention a l'unicode
** attention aussi a comment on doit gerer l'int renvye quand il y a un \n
*/

int	ft_printf(char const *test, ...)
{
	va_list ap;
	t_lst *arg;
	int result;

	arg = parsing(test);
	result = 0;
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
			return (-1);
		}
		result = result + arg->nb;
		arg = destroy_elem(arg);
	}
	free_list(arg);
	// printf(GRN"\nResult after : %d\n", result);
	va_end(ap);
	return (result);
}
