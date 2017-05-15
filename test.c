/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosi <cosi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/05/15 19:18:27 by cosi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char const *str2;
	// char *copy;
	// t_lst *all;
	// t_lst *tmp;

	str = "etc   %d  %7.3d  %s\n";
	str2 = "end is .%4s. and start is .%4s.";
	// copy = "%% 2h32t \\%40hjd  %ls rewqt   t%tkkjgct    kkk%hhhhh\n";
	// all = parsing(copy);
	// tmp = all;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->arg);
	// 	tmp = tmp->next;
	// }
	// printf("End of displaying string with all list's elements before checking\n\n ----------------------------- CHECKING -----------------------------\n");
	// check_elem(&all);
	printf("Real printf gives:\n");
	printf(str, 12, 248, "test");
	printf("\n\n-------------------------------------------------------------\n\n");
	printf("Mine gives:\n");
	test(str, 12, 248, "test");
	// test(str2, "end", "start");
	return (0);
}
