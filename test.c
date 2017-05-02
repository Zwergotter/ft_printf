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

	str = "etc";
	copy = ft_strdup(str);
	test(str, 12.321);
	return (0);
}
