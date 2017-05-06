#include "ft_printf.h"
#include <stdio.h>

void	test(char const *test, ...)
{
	va_list ap;
	double nb;

	va_start(ap, test);
	nb = va_arg(ap, double);
	printf("%6.2f", nb);
	va_end(ap);
}

int	main()
{	
	char *str;
	char *copy;
	t_lst **all;
	t_lst *tmp;

	str = "etc";
	copy = "eft %wwwwwwwwwwwwwwwwwd   rewqt   %t";
	all = parsing(copy);
	tmp = *all;
	while (tmp->next)
	{
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
	test(str, 12.321);
	printf(copy, 10);
	return (0);
}
