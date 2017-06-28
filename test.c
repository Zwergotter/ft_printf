/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:49:24 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/28 18:06:15 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>

/*
** Attention a l'unicode
** attention aussi a comment on doit gerer l'int renvye quand il y a un \n
*/

void	test(char const *test, ...)
{
	va_list ap;
	t_lst *arg;
	int result;
	static char	*saved = NULL;

	arg = parsing(test);
	result = 0;
	check_elem(&arg);
	va_start(ap, test);
	while (arg)
	{
		if (arg->type == STR)
		{
			// printf("\n\n --------Entering for the %dtime putstr for basic string-------- \n", i);
			arg->nb = ft_strlen(arg->arg);
			while (*arg->arg)
					bufferize(&saved, *(arg->arg++), 1);
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
			displaying(&saved, arg, ap);
			// printf("\n --------End of displaying for %dtime-------- \n\n", i);
		}
		result = result + arg->nb;
		arg = arg->next;
	}
	ft_putstr(saved);
	va_end(ap);
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
