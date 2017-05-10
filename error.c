/*
** Displays message according to the error and then exits.
*/

#include "ft_printf.h"

void	error_displayed(t_error error)
{
	if (error == ARGUMENT)
		ft_putstr_fd("Argument is not valid\n", 2);
	if (error == MALLOC)
		ft_putstr_fd("Memory allocation failed\n", 2);
	exit(0);
}