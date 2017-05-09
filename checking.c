/*
** File to check all elements which begin by % one by one
** Apparently strings written juste after a specifier, even without a white space, are fine.
** But need to check stuff like "%wwwwwd" that can't be acceptable
*/

#include <stdio.h>
#include "ft_printf.h"

int is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
		return (1);
	return (0);
}

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

int checking(t_lst *elem)
{
	int len;
	int i;

	len = ft_strlen(elem->arg);
	if (len < 2 || (len == 2 && !is_specifier(elem->arg[len - 1])))
		return (0);
	i = 0;
	while (i < len)
	{
		if (!is_flag(elem->arg[i]) && !is_precision(elem->arg[i]) && !is_length(elem->arg[i]) && !ft_isdigit(elem->arg[i] + '0'))
			return (0);
		i++;
	}
	return (1);
}

int check_elem(t_lst **first)
{
	t_lst *tmp;

	tmp = *first;
	while (tmp)
	{
		if (tmp->type != STR)
			if (!checking(tmp))
				return (0);
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
	return (1);
}