/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/28 20:09:01 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>

/*
** Attention a l'unicode
** attention aussi a comment on doit gerer l'int renvye quand il y a un \n
*/

int	test(char const *test, ...)
{
	va_list ap;
	t_lst *arg;
	int result;
	static char *saved = NULL;

	arg = parsing(test);
	result = 0;
	check_elem(&arg);
	va_start(ap, test);
	while (arg)
	{
		if (arg->type == STR)
			bufferize_str(&saved, arg->arg, arg);
		if (arg->type == EMPTY)
			ft_putstr("");
		else
			displaying(arg, ap, &saved);
		printf(RED"\nNb read char : %d\n" RESET, arg->nb);
		result = result + arg->nb;
		printf(GRN"Result after : %d\n" RESET, result);
		arg = arg->next;
	}
	printf("%s", saved);
	va_end(ap);
	return (result);
}

int	main()
{	
	printf(RED"Hello word\n"RESET);
	printf("%s\n", "test");
	printf(MAG"#"CYN"%s"MAG"#\n"RESET, "Pretty");
	printf("lol""123""456\n");
	int *b;
	char const *str;
	char const *str2;
	char* l = setlocale(LC_ALL, "");

	if (l == NULL)
		printf("l est nul\n");
	str = "etc   -%#5X-  -%+2.5d- -%08d-  -%C- -%-10s- -%c- -%hd- -%04%- -%p-\n";
	str2 = "end is .%4s. and start is .%4s.";
	printf("Real printf gives:\n");
	printf(str, 128, 248, 127, L'✈', "mwar test", 'c', 4, &b);
	printf("\n\n-------------------------------------------------------------\n\n");
	printf("Mine gives:\n");
	test(str, 128, 248, 127, L'✈', "mwar test", 'c', 4, &b);
	// test(str2, "end", "start");
	return (0);
}
