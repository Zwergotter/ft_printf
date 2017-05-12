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

#define	STR 1
#define INT 2
#define WCHAR_T 3
#define WIN_T 4
#define VOID 5

typedef	enum		e_error
{
	ARGUMENT, MALLOC
}					t_error;

typedef struct		s_lst
{
    struct s_lst	*next;
    int				type;
    char			*arg;
    /*POUR LES OPTIONS*/
    char			flag;
    int 			width;
    int 			precision;
    char			length[2];
    char			specifier;
    // int				nb; POUR CALCULER RETURN (ATTENTION A %C)
}
					t_lst;
t_lst	*parsing(char *str);
int 	is_specifier(char c);
void 	check_elem(t_lst **first);
void	error_displayed(t_error error);
void	what_kind(t_lst *elem);

# endif
