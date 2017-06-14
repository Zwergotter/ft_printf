/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/05 16:33:15 by edeveze          ###   ########.fr       */
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
			// printf("\n\n --------Entering for the %dtime putstr for basic string-------- \n", i);
			ft_putstr(arg->arg);
			arg->nb = ft_strlen(arg->arg);
			// printf("\n --------End of basic string for %dtime-------- \n\n", i);
		}
		if (arg->type == EMPTY)
		{
			// printf("\n\n --------Entering for the %dtime empty-------- \n", i);
			ft_putstr("");
			// printf("\n --------End of empty for %dtime-------- \n\n", i);
		}
		else
		{
			// printf("\n\n --------Entering for the %dtime displaying-------- \n", i);
			displaying(arg, ap);
			// printf("\n --------End of displaying for %dtime-------- \n\n", i);
		}
		result = result + arg->nb;
		arg = arg->next;
	}
	va_end(ap);
}

int	main()
{	
	printf(RED"Hello word\n"RESET);
	printf("%s\n", "test");
	printf(MAG"#"CYN"%s"MAG"#\n"RESET, "Pretty");
	printf("lol""123""456\n");
	char const *str;
	char const *str2;

	str = "etc   -%5d-  -%+2.5d- -%08.d-  -%s- -\%-10s- -%c- -%hd-\n";
	str2 = "end is .%4s. and start is .%4s.";
	printf("Real printf gives:\n");
	printf(str, 12, 248, 127, "t††®®ßßåç∫πestøΩ", "mwar test", 'c', 4);
	printf("\n\n-------------------------------------------------------------\n\n");
	printf("Mine gives:\n");
	test(str, 12, 248, 127, "t††®®ßßåç∫πestøΩ", "mwar test", 'c', 4);
	// test(str2, "end", "start");
	return (0);
}
