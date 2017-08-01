/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:14 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/01 20:39:05 by edeveze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H


#ifndef COLOR_H
# define COLOR_H
# ifndef RED
#  define RED "\x1B[31m"
# endif
# ifndef GRN
#  define GRN "\x1B[32m"
# endif
# ifndef YEL
#  define YEL "\x1B[33m"
# endif
# ifndef BLU
#  define BLU "\x1B[34m"
# endif
# ifndef MAG
#  define MAG "\x1B[35m"
# endif
# ifndef CYN
#  define CYN "\x1B[36m"
# endif
# ifndef WHT
#  define WHT "\x1B[37m"
# endif
# ifndef PNK
#  define PNK "\x1B[95m"
# endif
# ifndef RESET
#  define RESET "\x1B[0m"
# endif
#endif
# include <stdarg.h>

/*
** Library for malloc, free and exit.
*/

# include <stdlib.h>

/*
** Library for write.
*/

# include <unistd.h>
# include <stdio.h>

# include "libft.h"

typedef	enum		e_error
{
	ARGUMENT, MALLOC
}					t_error;

typedef enum		e_type
{
	EMPTY, STR, ARG_STR, INT, U_INT, WCHAR_T, WCHAR_TSTR, WIN_T, VOID, CHAR,
	U_CHAR, SHORT_INT, USHORT_INT, LONG_INT, ULONG_INT, LLONG_INT,
	ULLONG_INT, INT_MAXT, UINT_MAXT, SIZE_T, PERCENT, NOARG_STR
}					t_type;

typedef struct		s_lst
{
	struct s_lst	*next;
	t_type			type;
	char			*arg;
	char			flag;
	char			hash;
	char			sign;
	char			zero;
	int				len;
	int				width;
	int				i_pre;
	char			pre;
	char			length[3];
	char			spe;
	int				nb;
}					t_lst;

typedef struct		s_one
{
	char			*str;
	wchar_t			*wstr;
	int				len;
	char			sign;
	char			*new;
	char			*hash;
	char			c;
	int				pre;
	int				width;
	int				signed_nb;
}					t_one;

t_lst				*parsing(char const *str);

int					is_specifier(char c);
int					is_flag(char c, t_lst *elem);
int					is_precision(char c, t_lst *elem);
int					is_length(char c);
int					everything_at_once(char c, t_lst *elem);

void				check_elem(t_lst **first);
void				error_displayed(t_error error);
void				what_type(t_lst *elem);

void				displaying(t_lst *list, va_list ap);

void				display_number(t_lst *list, va_list ap, t_one *one);

void				display_str(t_lst *list, va_list ap, t_one *one);
void				display_char(t_lst *list, int nb);

void				display_wchar(unsigned long int nb, t_lst *list);
void				display_wstr(va_list ap, t_lst *list);

void				upper_string(char *str);

void				write_str(char *str, t_lst *list);
void				write_c(char c, int nb, t_lst *list);

int					everything(char c);

#endif
