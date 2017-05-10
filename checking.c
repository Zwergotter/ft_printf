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
** Order a gerer, flag -> width -> precision -> length
** un ou plusieurs de ceux ci peuvent etre zappes mais l'ordre doit etre respecte
** GERER aussi le %%
*/
int checking(t_lst *elem)
{
	int len;
	int i;
	int j;

	len = ft_strlen(elem->arg);
	if (len < 2 || (len == 2 && !is_specifier(elem->arg[len - 1]))) //////////////////////////////////////%%
		return (0);
	i = 1;
	if (is_flag(i))
			elem->flag = elem->arg[i++];
	while (i < len - 2 && (ft_isdigit(elem->arg[i]) || is_precision(elem->arg[i])))
	{
		if ((ft_isdigit(elem->arg[i] + '0') && !elem->precision) || (is_precision(elem->arg[i]) && ft_isdigit(elem->arg[i++] + '0')))
		{
			j = i;
			while (i < len - 2 && ft_isdigit(elem->arg[i] + '0'))
				i++;
			if (is_precision(elem->arg[j - 1]))
				elem->precision = ft_atoi(ft_strsub(elem->arg, j, i - j));
			else
				elem->width = ft_atoi(ft_strsub(elem->arg, j, i - j));
		}
		else
			return (0);
		// if (!is_flag(elem->arg[i]) && !is_precision(elem->arg[i]) && !is_length(elem->arg[i]) && !ft_isdigit(elem->arg[i] + '0'))
		// 	return (0);
		// i++;
	}
	if (is_length(elem->arg[i]))
			elem->length = elem->arg[i++];
	if (len - 1 != i)
		return (0);
	return (1);
}

void check_elem(t_lst **first)
{
	t_lst *tmp;
	t_error error;

	tmp = *first;
	error = ARGUMENT;
	while (tmp)
	{
		if (tmp->type != STR)
			if (!checking(tmp))
				error_displayed(error);
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
}