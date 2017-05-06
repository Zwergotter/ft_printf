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
	if ((elem->arg = (char*)malloc(sizeof(char) * end - start)) == NULL)
		return ;
	elem->type = STR;
	elem->arg = ft_strsub(str, start, end);
	elem->next = NULL;
	addlast(begin, elem);
}

void percent(t_lst **begin, char *str, int start)
{	
	t_lst *elem;
	int end;

	end = start;
	while (str[end])
	{
		while (!is_specifier(str[end]))
			end++;
		break ;
	}
	end = end - 1;
	printf("STILL WORKING PERCENT\n");
	if ((elem->arg = (char*)malloc(sizeof(char) * end - start)) == NULL)
		return ;
	printf("STILL WORKING PERCENT\n");
	elem->type = INT;
	elem->arg = ft_strsub(str, start, end);
	elem->next = NULL;
	addlast(begin, elem);
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
			if ((first->arg = (char*)malloc(sizeof(char) * i - 1)) == NULL)
				return (NULL);
			first->type = STR;
			first->arg = ft_strsub(str, 0, i - 1);
			first->next = NULL;
		}
		else
		{
			i++;
			while (str[i])
			{
				while (!is_specifier(str[i]))
					i++;
				break ;
			}
			if ((first->arg = (char*)malloc(sizeof(char) * i - 1)) == NULL)
				return (NULL);
			first->type = INT;
			first->arg = ft_strsub(str, 0, i - 1);
			first->next = NULL;
		}
		break ;
	}
	while (str[i])
	{
		j = i;
		while (str[j] != '%')
			j++;
		if (str[j - 1] && i != j)
			string(&first, str, i, j - 1);
		else
		{
			j++;
			percent(&first, str, j - 1);
		}
		i = j;
	}
	printf("STILL WORKING\n");
	return (first);
}

t_lst **parsing(char *str)
{
	t_lst **lst;

	*lst = first_one(str);
	return (lst);
}