#include "ft_printf.h"
#include <stdio.h>

void displaying(t_lst *list, va_list ap)
{
	int result;

	if (list->type == INT)
	{
		result = va_arg(ap, int);
		ft_putnbr(result);
		list->nb = ft_countdigits(result);
	}
}


/*
** Attention a l'unicode
*/

void	test(char const *test, ...)
{
	va_list ap;
	t_lst *arg;

	arg = parsing(test);
	check_elem(&arg);
	va_start(ap, test);
	while (arg)
	{
		if (arg->type == STR)
			{
				ft_putstr(arg->arg);
				arg->nb = ft_strlen(arg->arg);
			}
		else
			displaying(arg, ap);
		arg = arg->next;
	}
	va_end(ap);
}

int	main()
{	
	char const *str;
	char *copy;
	t_lst *all;
	t_lst *tmp;

	str = "etc   %d  %d";
	copy = "%% 2h32t \\%40hjd  %ls rewqt   t%tkkjgct    kkk%hhhhh\n";
	all = parsing(copy);
	tmp = all;
	while (tmp)
	{
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
	printf("End of displaying string with all list's elements before checking\n\n ----------------------------- CHECKING -----------------------------\n");
	check_elem(&all);
	test(str, 12, 24);
	return (0);
}
