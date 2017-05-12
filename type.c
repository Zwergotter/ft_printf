#include "ft_printf.h"
#include <stdio.h>

void 	type_unsigned(t_lst *elem)
{
	if (!ft_strcmp(elem->length, "l"))
		elem->type = ULONG_INT;
	if (!ft_strcmp(elem->length, "ll"))
		elem->type = ULLONG_INT;
	if (!ft_strcmp(elem->length, "h"))
		elem->type = USHORT_INT;
	if (!ft_strcmp(elem->length, "hh"))
		elem->type = U_CHAR;
	if (!ft_strcmp(elem->length, "j"))
		elem->type = UINT_MAX;
	if (!ft_strcmp(elem->length, "z"))
		elem->type = SIZE_T;
	else
		elem->type = U_INT;
}

void 	type_signed(t_lst *elem)
{
	if (!ft_strcmp(elem->length, "l"))
		elem->type = LONG_INT;
	if (!ft_strcmp(elem->length, "ll"))
		elem->type = LLONG_INT;
	if (!ft_strcmp(elem->length, "h"))
		elem->type = SHORT_INT;
	if (!ft_strcmp(elem->length, "hh"))
		elem->type = CHAR;
	if (!ft_strcmp(elem->length, "j"))
		elem->type = INT_MAX;
	if (!ft_strcmp(elem->length, "z"))
		elem->type = SIZE_T;
	else
		elem->type = INT;
}

void	what_type(t_lst *elem)
{
	if (elem->specifier == 's' || elem->specifier == 'S')
	{
		if (ft_strcmp(elem->length, "l"))
			elem->type = STR;
		else
			elem->type = WCHAR_T;
	}
	if (elem->specifier == 'c' || elem->specifier == 'C')
	{
		if (ft_strcmp(elem->length, "l"))
			elem->type = INT;
		else
			elem->type = WIN_T;
	}
	if (elem->specifier == 'p')
		elem->type = VOID;
	if (elem->specifier == 'd' || elem->specifier == 'D' || elem->specifier == 'i')
		type_signed(elem);
	if (elem->specifier == '%')
		return ;
	else
		type_unsigned(elem);
}