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
	int len;

	len = end - start;
	if ((elem = (t_lst*)malloc((sizeof(char) * (end - start)) + sizeof(int) + sizeof(t_lst))) == NULL)
		return ;
	elem->type = STR;
	elem->arg = ft_strsub(str, start, len);
	elem->next = NULL;
	addlast(begin, elem);
}

void percent(t_lst **begin, char *str, int start, int end)
{	
	t_lst *elem;
	int len;

	if ((elem = (t_lst*)malloc((sizeof(char) * (end - start)) + sizeof(int) + sizeof(t_lst))) == NULL)
		return ;
	if (is_specifier(str[end]))
		end = end + 1;
	len = end - start;
	elem->arg = ft_strsub(str, start, len);
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
			if ((first = (t_lst*)malloc((sizeof(char) * (i - 1)) + sizeof(int) + sizeof(t_lst))) == NULL)
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
		}
		break ;
	}
	while (str[i])
	{
		j = i;
		while (str[j] && str[j] != '%')
			j++;
		if (j > i && (str[j] == '%' || !str[j]))
			string(&first, str, i, j);
		else
		{
			j++;
			while (str[j] && !(is_specifier(str[j])))
				j++;
			if (is_specifier(str[j]))
				j = j + 1;
			percent(&first, str, i, j);
		}
		i = j;
	}
	return (first);
}

t_lst *parsing(char *str)
{
	t_lst *lst;

	lst = first_one(str);
	return (lst);
}