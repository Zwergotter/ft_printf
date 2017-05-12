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
	t_lst *tmp;

	str = "etc";
	// backslash pas pris en compte????????????
	copy = "2h32t \\%40hjd  %ls rewqt   t%tkkjgct    kkk%hhhhh\n";
	all = parsing(copy);
	tmp = all;
	while (tmp)
	{
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
	printf("End of displaying string with all list's elements before checking\n\n ----------------------------- CHECKING -----------------------------\n");
	check_elem(&all);
	// test(str, 12.321);
	// printf(copy, 10);
	return (0);
}
