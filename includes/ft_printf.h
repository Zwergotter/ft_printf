/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:14 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/05 16:22:29 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

/*
** Library for malloc, free and exit.
*/

# include <stdlib.h>

/*
** Library for write.
*/

# include <unistd.h>

# include "libft.h"

typedef	enum		e_error
{
	ARGUMENT, MALLOC
}					t_error;

typedef enum		e_type
{
	EMPTY, STR, ARG_STR, INT, U_INT, WCHAR_T, WIN_T, VOID, CHAR, U_CHAR,
	SHORT_INT, USHORT_INT, LONG_INT, ULONG_INT, LLONG_INT, ULLONG_INT,
	INT_MAXT, UINT_MAXT, SIZE_T, PERCENT
}					t_type;

typedef struct		s_lst
{
	struct s_lst	*next;
	t_type			type;
	char			*arg;
	char			flag;
	int				len;
	int				width;
	int				i_pre;
	char 			pre;
	char			length[2];
	char			spe;
	int				nb;
    //POUR CALCULER RETURN (ATTENTION A %C)
}					t_lst;

typedef struct		s_one
{
	char			*str;
	int				len;
	char 			sign;
	char 			*new;
	char 			c;
	int 			diff_pre;
	int 			diff_width;
}					t_one;

t_lst	*parsing(char const *str);

int		is_specifier(char c);
int		is_flag(char c, t_lst *elem);
int		is_precision(char c, t_lst *elem);
int		is_length(char c);
int 	everything_at_once(char c, t_lst *elem);

void	check_elem(t_lst **first);
void	error_displayed(t_error error);
void	what_type(t_lst *elem);
void	displaying(t_lst *list, va_list ap);

#endif
