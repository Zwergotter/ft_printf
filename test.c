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
	t_lst *all;

	str = "etc";
	copy = "2h32t %wwwwwwwwwwwwwwwwwd   rewqt   t%tkkjgct    kkk";
	all = parsing(copy);
	while (all)
	{
		printf("%s-\n", all->arg);
		all = all->next;
	}
	// test(str, 12.321);
	// printf(copy, 10);
	return (0);
}
