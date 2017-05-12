#include "ft_printf.h"
#include <stdio.h>

void 	type_unsigned(t_lst *elem)
{
	elem->type = U_INT;
	if ((ft_strcmp(elem->length, "l")) == 0)
		elem->type = ULONG_INT;
	if ((ft_strcmp(elem->length, "ll")) == 0)
		elem->type = ULLONG_INT;
	if ((ft_strcmp(elem->length, "h")) == 0)
		elem->type = USHORT_INT;
	if ((ft_strcmp(elem->length, "hh")) == 0)
		elem->type = U_CHAR;
	if ((ft_strcmp(elem->length, "j")) == 0)
		elem->type = UINT_MAXT;
	if ((ft_strcmp(elem->length, "z")) == 0)
		elem->type = SIZE_T;
}

void 	type_signed(t_lst *elem)
{
	elem->type = INT;
	if ((ft_strcmp(elem->length, "l")) == 0)
		elem->type = LONG_INT;
	if ((ft_strcmp(elem->length, "ll")) == 0)
		elem->type = LLONG_INT;
	if ((ft_strcmp(elem->length, "h")) == 0)
		elem->type = SHORT_INT;
	if ((ft_strcmp(elem->length, "hh")) == 0)
		elem->type = CHAR;
	if ((ft_strcmp(elem->length, "j")) == 0)
		elem->type = INT_MAXT;
	if ((ft_strcmp(elem->length, "z")) == 0)
		elem->type = SIZE_T;
}

void	what_type(t_lst *elem)
{
	if (elem->specifier == '%')
		return ;
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
	if (elem->specifier == 'u' || elem->specifier == 'U' || elem->specifier == 'o'|| elem->specifier == 'O' || elem->specifier == 'x' || elem->specifier == 'X')
		type_unsigned(elem);
}