#include "ft_printf.h"
#include <stdio.h>

void	what_kind(t_lst *elem)
{
	printf("ENTERING IN ONE KIND\n");
	if (elem->specifier == 's' || elem->specifier == 'S')
	{
		printf("strcmp is %d\n", ft_strcmp(elem->length, "l"));
		if (ft_strcmp(elem->length, "l"))
			elem->type = STR;
		else
			elem->type = WCHAR_T;
	}
	if (elem->specifier == 'c' || elem->specifier == 'C')
	{
		if (!ft_strcmp(elem->length, "l"))
			elem->type = WIN_T;
		else
			elem->type = INT;
	}
	if (elem->specifier == 'p')
		elem->type = VOID;
}