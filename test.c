/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/07/19 17:56:34 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>

/*
** Switches to next element of a list and destroys the previous one
*/

t_lst	*destroy_elem(t_lst *elem)
{
	t_lst *tmp;

	tmp = elem;
	elem = elem->next;
	free(tmp);
	return (elem);
}

/*
** This function is called when in printf we encounter a string or an invalid
** format which will be interpert as a string on its own, no argument string.
** This kind can still have flags like 0 or - and it must display these as well
*/

void	only_string(t_lst *arg)
{
	int len;

	len = ft_strlen(arg->arg);
	if (arg->type == NOARG_STR && arg->width && arg->flag != '-')
	{
		(arg->zero == '0' ? write_c('0', arg->width - len, arg) :
			write_c(' ', arg->width - len, arg));
		arg->width = 0;
	}
	write_str(arg->arg, arg);
	if (arg->type == NOARG_STR && arg->width)
		write_c(' ', arg->width - len, arg);
}

/*
** Ft_printf will first parse all strings and conversion's formats in a list
** where each element is known as one kind or the other.
** Then it calls check_elem to save all information such as length, flags etc.
** And finally it's calling one by one each element and, if necessary, in
** displaying, the argument.
** Finally returns all number of characters read.
*/

int		ft_printf(char const *test, ...)
{
	va_list	ap;
	t_lst	*arg;
	int		result;

	arg = parsing(test);
	result = 0;
	check_elem(&arg);
	va_start(ap, test);
	while (arg && arg->type != EMPTY)
	{
		if (arg->type == STR || arg->type == NOARG_STR)
			only_string(arg);
		else
			displaying(arg, ap);
		if (arg->nb == -1)
			return (-1);
		result = result + arg->nb;
		arg = destroy_elem(arg);
	}
	printf(GRN"\nResult after : %d\n", result);
	va_end(ap);
	return (result);
}

int		main()
{	
	// char* l = setlocale(LC_ALL, "");

	// if (l == NULL)
		// printf("l est nul\n");
	int i;
	char c;

	c = 128;
	printf("\n\n-------------------------------------------------------------\n");
	printf(CYN"C 我\n");
	printf(RED"Real printf gives:\n");
	printf(" result : %d\n"RESET, printf("%C et", c));
	printf("\nMine gives:\n");
	i = ft_printf("%C et", c);
	printf("Result = %d", i);
	printf("\n");


	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"4s Jambon\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%4s", L"Jambon"));
	// printf("\nMine gives:\n");
	// ft_printf("%4s", L"Jambon");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"4d 159\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%4d", 159));
	// printf("\nMine gives:\n");
	// ft_printf("%4d", 159);
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"30S 我是一只猫。\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%30S", L"我是一只猫。"));
	// printf("\nMine gives:\n");
	// ft_printf("%30S", L"我是一只猫。");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"-30S 我是一只猫。\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%-30S", L"我是一只猫。"));
	// printf("\nMine gives:\n");
	// ft_printf("%-30S", L"我是一只猫。");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"15.4S 我是一只猫。\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%15.4S", L"我是一只猫。"));
	// printf("\nMine gives:\n");
	// ft_printf("%15.4S", L"我是一只猫。");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN".4S 我是一只猫。\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%.4S", L"我是一只猫。"));
	// printf("\nMine gives:\n");
	// ft_printf("%.4S", L"我是一只猫。");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"4.S 我是一只猫。\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%4.S", L"我是一只猫。"));
	// printf("\nMine gives:\n");
	// ft_printf("%4.S", L"我是一只猫。");
	// printf("\n");

	// printf("\n\n-------------------------------------------------------------\n");
	// printf(CYN"4.1S Jambon\n");
	// printf(RED"Real printf gives:\n");
	// printf(" result : %d\n"RESET, printf("%4.1S", L"Jambon"));
	// printf("\nMine gives:\n");
	// ft_printf("%4.1S", L"Jambon");
	// printf("\n");
	return (0);
}
