/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:14 by edeveze           #+#    #+#             */
/*   Updated: 2017/04/26 18:57:49 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>

/*
** Library for malloc, free and exit.
*/

#include <stdlib.h>

/*
** Library for write.
*/

#include <unistd.h>

#include "libft.h"

typedef	enum		e_error
{
	ARGUMENT, MALLOC
}					t_error;

typedef enum 		e_type
{
	EMPTY, STR, ARG_STR, INT, U_INT, WCHAR_T, WIN_T, VOID, CHAR, U_CHAR, SHORT_INT, USHORT_INT, LONG_INT, ULONG_INT, LLONG_INT,
	ULLONG_INT, INT_MAXT, UINT_MAXT, SIZE_T, PERCENT
}					t_type;

typedef struct		s_lst
{
    struct s_lst	*next;
    t_type 			type;
    char			*arg;
    /*POUR LES OPTIONS*/
    char			flag;
    int 			width;
    int 			precision;
    char			length[2];
    char			specifier;
    int				nb; 
    //POUR CALCULER RETURN (ATTENTION A %C)
}
					t_lst;

t_lst	*parsing(char const *str);
int 	is_specifier(char c);
void 	check_elem(t_lst **first);
void	error_displayed(t_error error);
void	what_type(t_lst *elem);
void    displaying(t_lst *list, va_list ap);

# endif
