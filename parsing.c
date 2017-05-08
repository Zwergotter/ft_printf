#include "ft_printf.h"
#include <stdio.h>

void	addlast(t_lst **begin, t_lst *new)
{
	t_lst	*lst;

	lst = *begin;
	if (lst == 0)
		return ;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

int is_specifier(char c)
{
	if (c == 's' || c == 'S' || c == 'p'
			|| c == 'd' || c == 'D' || c == 'i' ||
			c == 'o' || c == 'O' || c == 'u' ||
			c == 'U' || c == 'x' || c == 'X' ||
			c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

void string(t_lst **begin, char *str, int start, int end)
{	
	t_lst *elem;

	printf("STILL WORKING STR\n");
	if ((elem = (t_lst*)malloc((sizeof(char) * (end - start)) + sizeof(int) + sizeof(t_lst))) == NULL)
		return ;
	elem->type = STR;
	elem->arg = ft_strsub(str, start, end);
	elem->next = NULL;
	addlast(begin, elem);
	printf("END STR\n");
	printf("%s\n", elem->arg);
}

void percent(t_lst **begin, char *str, int start, int end)
{	
	t_lst *elem;

	// printf("STILL WORKING PERCENT\n");
	if ((elem = (t_lst*)malloc((sizeof(char) * (end - start)) + sizeof(int) + sizeof(t_lst))) == NULL)
		return ;
	if (is_specifier(str[end]))
		end = end + 1;
	elem->arg = ft_strsub(str, start, end);
	elem->next = NULL;
	addlast(begin, elem);
	// printf("END PERCENT\n");
	// printf("%s\n", elem->arg);
}

t_lst *first_one(char *str)
{
	int i;
	int j;
	t_lst *first;

	i = 0;
	while (str[i])
	{
		while (str[i] != '%')
			i++;
		if (i != 0)
		{
			if ((first = (t_lst*)malloc((sizeof(char) * (i - 1)) + sizeof(int) + sizeof(t_lst))) == NULL)
				return (NULL);
			first->type = STR;
			first->arg = ft_strsub(str, 0, i - 1);
			first->next = NULL;
			printf("DONE FIRST STR\n");
			printf("is %s-\n", first->arg);
		}
		else
		{
			i++;
			while (str[i])
			{
				while (str[i] && !is_specifier(str[i]))
					i++;
				break ;
			}
			if ((first = (t_lst*)malloc((sizeof(char) * (i - 1)) + sizeof(int) + sizeof(t_lst))) == NULL)
				return (NULL);
			first->type = INT;
			if (is_specifier(str[i]))
				i = i + 1;
			first->arg = ft_strsub(str, 0, i);
			first->next = NULL;
			printf("DONE FIRST PERCENT\n");
			printf("is %s-\n", first->arg);
		}
		break ;
	}
	printf("where is i %c-\n", str[i]);
	while (str[i])
	{
		j = i;
		while (str[j] && str[j] != '%')
			j++;
		if (j > i && (str[j] == '%' || !str[j]))
		{
			string(&first, str, i, j);
			printf("j is %c-\n", str[j]);
		}
		else
		{
			while (str[j] && !(is_specifier(str[j])))
				j++;
			printf("j is %c-\n", str[j]);
			if (is_specifier(str[j]))
				j = j + 1;
			percent(&first, str, i, j);
			printf("j is %c-\n", str[j]);
		}
		i = j;
	}
	// while (str[i])
	// {
	// 	// j = i;
	// 	// while (str[j] != '%' && str[j])
	// 	// 	j++;
	// 	// if (j > i)
	// 	// {
	// 	// 	if (is_specifier(str[j]))
	// 	// 		j = j + 1;
	// 	// 	string(&first, str, i, j);
	// 	// }
	// 	// else
	// 	// {
	// 	// 	while(str[j] && !is_specifier(str[j]))
	// 	// 		j++;
	// 	// 	if (is_specifier(str[j]))
	// 	// 		j = j + 1;
	// 	// 	percent(&first, str, i, j);
	// 	// }
	// 	// i = j;
	// 	// printf("STILL WORKING IN MAIN LOOP\n");
	// }
	printf("FINISHING\n");
	return (first);
}

t_lst *parsing(char *str)
{
	t_lst *lst;

	lst = first_one(str);
	printf("DONE PARSING\n");
	return (lst);
}