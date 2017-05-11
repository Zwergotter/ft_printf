#include "ft_printf.h"
#include <stdio.h>

/*
** Scans a list thanks to its first element and puts the new one at the last position.
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
** Functions to identify a specifier.
*/

int is_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p'
			|| c == 'd' || c == 'D' || c == 'i' ||
			c == 'o' || c == 'O' || c == 'u' ||
			c == 'U' || c == 'x' || c == 'X' ||
			c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

/*
** Creating just one element that contains a string and finished before a specifier or because the string has ended.
** Puts this element at the list's end.
*/

void string(t_lst **begin, char *str, int start, int end)
{	
	t_lst *elem;
	t_error error;
	int len;

	error = MALLOC;
	len = end - start;
	if ((elem = (t_lst*)malloc((sizeof(char) * (end - start) + 3) + (sizeof(int) * 3) + sizeof(t_lst))) == NULL)
		error_displayed(error);
	elem->type = STR;
	elem->arg = ft_strsub(str, start, len);
	elem->next = NULL;
	addlast(begin, elem);
}

/*
** Creating just one element that starts with a percent and finished with a specifier or because the string has ended.
** Puts this element at the list's end.
*/

void percent(t_lst **begin, char *str, int start, int end)
{	
	t_lst *elem;
	t_error error;
	int len;

	error = MALLOC;
	if ((elem = (t_lst*)malloc((sizeof(char) * (end - start) + 3) + (sizeof(int) * 3) + sizeof(t_lst))) == NULL)
		error_displayed(error);
	if (is_specifier(str[end]))
		end = end + 1;
	len = end - start;
	elem->arg = ft_strsub(str, start, len);
	elem->next = NULL;
	addlast(begin, elem);
}

/*
** Creating first element and following ones and linked to the first in order to have a list.
*/

t_lst *first_one(char *str)
{
	int i;
	int j;
	t_lst *first;
	t_error error;

	error = MALLOC;
	i = 0;
	while (str[i])
	{
		while (str[i] != '%')
			i++;
		if (i != 0)
		{
			if ((first = (t_lst*)malloc((sizeof(char) * (i + 2)) + (sizeof(int) * 3) + sizeof(t_lst))) == NULL)
				error_displayed(error);
			first->type = STR;
			first->arg = ft_strsub(str, 0, i - 1);
			first->next = NULL;
		}
		else
		{
			i++;
			while (str[i])
			{
				while (str[i] && !is_specifier(str[i]))
					i++;
				break ;
			}
			if ((first = (t_lst*)malloc((sizeof(char) * (i + 2)) + (sizeof(int) * 3) + sizeof(t_lst))) == NULL)
				error_displayed(error);
			if (is_specifier(str[i]))
				i = i + 2;
			first->arg = ft_strsub(str, 0, i);
			first->next = NULL;
		}
		break ;
	}
	while (str[i])
	{
		j = i;
		while (str[j] && str[j] != '%')
			j++;
		if (j > i && (str[j] == '%' || !str[j]))
			string(&first, str, i, j);
		else
		{
			j++;
			while (str[j] && !(is_specifier(str[j])))
				j++;
			if (is_specifier(str[j]))
				j = j + 1;
			percent(&first, str, i, j);
		}
		i = j;
	}
	return (first);
}

/*
** Parsing all the string in one list with elements
*/

t_lst *parsing(char *str)
{
	t_lst *lst;

	lst = first_one(str);
	return (lst);
}