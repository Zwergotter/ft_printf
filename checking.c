/*
** File to check all elements which begin by % one by one
** Apparently strings written juste after a specifier, even without a white space, are fine.
** But need to check stuff like "%wwwwwd" that can't be acceptable
*/

#include <stdio.h>
#include "ft_printf.h"

int is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
		return (1);
	return (0);
}

/*
** Nombre avant . -> sont la taille. Sinon, c'est la precision.
*/

int is_precision(char c)
{
	if (c == '.')
		return (1);
	return (0);
}

/*
** ATTENTION. Aussi hh et ll a gerer.
*/
int is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return(0);
}

/*
** Checking all at once
*/

int everything_at_once(char c)
{
	if (ft_isdigit(c + 0) || is_precision(c) || is_length(c) || is_flag(c))
		return (1);
	return (0);
}

/*
** Order a gerer, flag -> width -> precision -> length
** un ou plusieurs de ceux ci peuvent etre zappes mais l'ordre doit etre respecte
** GERER aussi le %%
*/

int checking(t_lst *elem)
{
	int len;
	int i;
	int j;
	char *str;

	len = ft_strlen(elem->arg);
	if (len < 2)
		return (0); // rien a afficher?
	i = 1;
	while (i < len - 1 && everything_at_once(elem->arg[i]))
	{
		printf("IN LOOP\n");
		if ((ft_isdigit(elem->arg[i] + 0) && !elem->precision) || (is_precision(elem->arg[i]) && ft_isdigit(elem->arg[i++] + 0)))
		{ //que se passe t il aved la precision s'il y a uniquement "."?"
			j = i;
			printf("Where is j: %c \n", elem->arg[j]);
			while (i < len - 2 && ft_isdigit(elem->arg[i] + 0))
				i++;
			if (is_precision(elem->arg[j - 1]))
			{
				elem->precision = ft_atoi(&(elem->arg[j]));
				printf("PRECISION IS %d\n", elem->precision);
			}
			else
			{
				elem->width = ft_atoi(&(elem->arg[j]));
				printf("WIDTH IS %d\n", elem->width);
			}
		}
		if (is_length(elem->arg[i]))
		{
			elem->length = elem->arg[i++];
			printf("LENGTH IS %c\n", elem->length);
		}
		if (is_flag(elem->arg[i]))
		{
			elem->flag = elem->arg[i++];
			printf("FLAG IS %c\n", elem->flag);
		}
	}
	if (is_specifier(elem->arg[i]))
	{
		elem->specifier = elem->arg[i];
		printf("SPECIFIER IS %c\n", elem->specifier);
		//si pas fin de string, nouvel elem a faire et a mettre entre les deux ave le reste de str // ou NON? car deja fait cela en amont
	}
	else
	{
		printf("NO SPECIFIER FOUND\n");
		str = elem->arg;
		printf("elem arg before change is: %s\n",elem->arg);
		elem->type = STR;
		elem->arg = ft_strsub(str, i, len - i);
		free(str);
		printf("elem arg after change is: %s\n",elem->arg);
		//gerer si longueur quelconque repertoriee.

	}
	return (1);
}

void check_elem(t_lst **first)
{
	t_lst *tmp;
	t_error error;

	tmp = *first;
	error = ARGUMENT;
	while (tmp)
	{
		if (tmp->type != STR)
			if (!checking(tmp))
				error_displayed(error);
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
}