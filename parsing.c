/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:42:47 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/17 22:53:54 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Scans a list thanks to its first element and puts the new one at the end.
*/

void	addlast(t_lst **begin, t_lst *new)
{
	t_lst	*lst;

	lst = *begin;
	if (lst == 0)
		return ;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

/*
** Creating just one element that contains a string and finished before a
** specifier or because the string has ended.
** Puts this element at the list's end.
*/

t_lst	*string(char const *str, int start, int end)
{
	t_lst	*elem;
	int		len;

	len = end - start;
	if ((elem = (t_lst*)malloc(sizeof(t_lst))) == NULL)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(0);
	}
	ft_bzero(elem, (sizeof(t_lst)));
	elem->type = (str[start] == '%' ? NOARG_STR : STR);
	elem->arg = (str[start] == '%' ? ft_strsub(str, start + 1, len)
		: ft_strsub(str, start, len));
	elem->len = ft_strlen(elem->arg);
	elem->next = NULL;
	return (elem);
}

/*
** Creating just one element that starts with a percent and finished with a
** specifier or because the string has ended.
** Puts this element at the list's end.
*/

t_lst	*percent(char const *str, int start, int end)
{
	t_lst	*elem;
	int		len;

	if ((elem = (t_lst*)malloc(sizeof(t_lst))) == NULL)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(0);
	}
	ft_bzero(elem, (sizeof(t_lst)));
	if (is_specifier(str[end]))
		end = end + 1;
	len = end - start;
	elem->arg = ft_strsub(str, start, len);
	elem->len = ft_strlen(elem->arg);
	elem->next = NULL;
	return (elem);
}

/*
** Creates element one by one and adds them at the list's end
*/

void	creating_list(t_lst **begin, const char *str, int i)
{
	int		j;

	while (str[i])
	{
		j = i;
		while (str[j] && str[j] != '%')
			j++;
		if (j > i && (str[j] == '%' || !str[j]))
			addlast(begin, string(str, i, j));
		else
		{
			j++;
			while (str[j] && everything(str[j]) && !is_specifier(str[j]))
				j++;
			if (is_specifier(str[j]))
				addlast(begin, percent(str, ++i, ++j));
			else
				addlast(begin, string(str, i, (str[j] ? j++ : j)));
		}
		i = j;
	}
}

/*
** Creating first element and then calling creating_list to link
** next elements.
*/

t_lst	*parsing(char const *str)
{
	int		i;
	t_lst	*first;

	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	if (i != 0)
		first = string(str, 0, i);
	else
	{
		i++;
		while (str[i] && everything(str[i]) && !is_specifier(str[i]))
			i++;
		if (is_specifier(str[i]))
			first = percent(str, 1, i++);
		else
			first = string(str, 0, (str[i] ? i++ : i));
	}
	if (str[i])
		creating_list(&first, str, i);
	return (first);
}
