#include "ft_printf.h"
#include <stdio.h>

/*
** Attention a l'unicode
** attention aussi a comment on doit gerer l'int renvye quand il y a un \n
*/

void	test(char const *test, ...)
{
	va_list ap;
	t_lst *arg;
	int result;

	arg = parsing(test);
	result = 0;
	check_elem(&arg);
	va_start(ap, test);
	while (arg)
	{
		if (arg->type == STR)
		{
			ft_putstr(arg->arg);
			arg->nb = ft_strlen(arg->arg);
		}
		if (arg->type == EMPTY)
			ft_putstr("");
		else
			displaying(arg, ap);
		result = result + arg->nb;
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

	str = "etc   %d  %d  %s\n";
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
	test(str, 12, 24, "test");
	return (0);
}
