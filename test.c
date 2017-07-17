/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/17 17:09:55 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>

t_lst *destroy_elem(t_lst *elem)
{
	t_lst *tmp;

	tmp = elem;
	elem = elem->next;
	free (tmp);
	return (elem);
}

/*
** Attention a l'unicode
** attention aussi a comment on doit gerer l'int renvye quand il y a un \n
*/

int	test(char const *test, ...)
{
	va_list ap;
	t_lst *arg;
	int result;

	arg = parsing(test);
	result = 0;
	check_elem(&arg);
	va_start(ap, test);
	while (arg && arg->type != EMPTY)
	{
		if (arg->type == STR || arg->type == NOARG_STR)
		{
			if (arg->type == NOARG_STR && arg->width && arg->flag != '-')
			{
				(arg->zero == '0' ? write_c('0', arg->width - (ft_strlen(arg->arg)), arg) : write_c(' ', arg->width - (ft_strlen(arg->arg)), arg));
				arg->width = 0;
			}
			write_str(arg->arg, arg);
			if (arg->type == NOARG_STR && arg->width)
				write_c(' ', arg->width - (ft_strlen(arg->arg)), arg);
		}
		else
			displaying(arg, ap);
		// printf(RED"\nNb read char : %d\n" RESET, arg->nb);
		result = result + arg->nb;
		// printf(GRN"Result after : %d\n" RESET, result);
		arg = destroy_elem(arg);
	}
	printf(GRN"\nResult after : %d\n", result);
	va_end(ap);
	return (result);
}

int	main()
{	
	char* l = setlocale(LC_ALL, "");

	if (l == NULL)
		printf("l est nul\n");

	printf("\n\n-------------------------------------------------------------\n");
	printf(CYN"05.Z\n");
	printf(RED"Real printf gives:\n");
	printf(" result : %d\n"RESET, printf("{%05.Z}", 0));
	printf("\nMine gives:\n");
	test("{%05.Z}", 0);
	printf("\n");

// STILL
	printf("\n\n-------------------------------------------------------------\n");
	printf(CYN"05.S L 42 c est cool\n");
	printf(RED"Real printf gives:\n");
	printf(" result : %d\n"RESET, printf("{%05.S}", L"42 c est cool"));
	printf("\nMine gives:\n");
	test("{%05.S}", L"42 c est cool");
	printf("\n");

	printf("\n\n-------------------------------------------------------------\n");
	printf(CYN"{-15Z}, 123\n");
	printf(RED"Real printf gives:\n");
	printf(" result : %d\n"RESET, printf("{%-15Z}", 123));
	printf("\nMine gives:\n");
	test("{%-15Z}", 123);
	printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"Z\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%Z"));
	// printf("\nMine gives:\n");
	// test("%Z");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN" hZ\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("% hZ%"));
	// printf("\nMine gives:\n");
	// test("% hZ%");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"Z, s, test\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("% Z%s", "test"));
	// printf("\nMine gives:\n");
	// test("% Z%s", "test");
	// printf("\n");



	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"4.15S 我是一只猫。\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%4.15S", L"我是一只猫。"));
	// printf("\nMine gives:\n");
	// test("%4.15S", L"我是一只猫。");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"15.4S 我是一只猫。\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%15.4S", L"我是一只猫。"));
	// printf("\nMine gives:\n");
	// test("%15.4S", L"我是一只猫。");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"4S 我是一只猫。\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%4.S", L"我是一只猫。"));
	// printf("\nMine gives:\n");
	// test("%4.S", L"我是一只猫。");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"4.1S Jambon\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%4.1S", L"Jambon"));
	// printf("\nMine gives:\n");
	// test("%4.1S", L"Jambon");
	// printf("\n");
// END STILL

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"For .1x .5x and 0 0\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("@moulitest: %.1x %.5x", 0, 0));
	// printf("\nMine gives:\n");
	// test("@moulitest: %.1x %.5x", 0, 0);
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"For #.x #.0x and 0 0\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("@moulitest: %#.x %.0x", 0, 0));
	// printf("\nMine gives:\n");
	// test("@moulitest: %#.x %.0x", 0, 0);
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"For #.1x #.5x and 0 0\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("@moulitest: %#.1x %#.5x", 0, 0));
	// printf("\nMine gives:\n");
	// test("@moulitest: %#.1x %#.5x", 0, 0);
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"For 5.d 5.0d and 0 0\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("@moulitest: %5.d %5.0d", 0, 0));
	// printf("\nMine gives:\n");
	// test("@moulitest: %5.d %5.0d", 0, 0);
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"For 5.6d 5.2d and 0 0\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("@moulitest: %5.6d %5.2d", 0, 0));
	// printf("\nMine gives:\n");
	// test("@moulitest: %5.6d %5.2d", 0, 0);
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"For .x .0x and 0 0\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("@moulitest: %.x %.0x", 0, 0));
	// printf("\nMine gives:\n");
	// test("@moulitest: %.x %.0x", 0, 0);
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n\n");
	// printf(CYN"For -5.2 string with no arg\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%-5.2s is a string", ""));
	// printf("\nMine gives:\n");
	// test("%-5.2s is a string", "");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n\n");
	// printf(CYN"For 5.2 string with no arg\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%5.2s is a string", ""));
	// printf("\nMine gives:\n");
	// test("%5.2s is a string", "");
	// printf("\n");

	
	// printf(RED"Hello word\n"RESET);
	// printf("%s\n", "test");
	// printf(MAG"#"CYN"%s"MAG"#\n"RESET, "Pretty");
	// printf("lol""123""456\n");
	// int *b;
	// char const *str;
	// char const *str2;

	// str = "etc   -%#5X-  -%+2.5d- -%08d-  -%C- -%-10s- -%c- -%hd- -%04%- -%p-\n";
	// str2 = "end is .%4s. and start is .%4s.";
	// printf("Real printf gives:\n");
	// printf("result : %d\n", printf(str, 128, 248, 127, L'✈', "mwar test", 'c', 4, &b));
	// printf("\n\n-------------------------------------------------------------\n\n");
	// printf("\nMine gives:\n");
	// test(str, 128, 248, 127, L'✈', "mwar test", 'c', 4, &b);
	// test(str2, "end", "start");
	return (0);
}
