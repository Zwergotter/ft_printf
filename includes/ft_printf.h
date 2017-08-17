/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:14 by edeveze           #+#    #+#             */
/*   Updated: 2017/08/02 19:37:17 by edeveze          ###   ########.fr       */
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
# include <stdio.h>
# include <locale.h>
# include "libft.h"

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
	char			sp;
	int				nb;
}					t_lst;

typedef struct		s_one
{
	char			*str;
	wchar_t			*wstr;
	int				len;
	char			sign;
	char			*oth;
	char			*hash;
	char			c;
	int				pre;
	int				width;
	int				signed_nb;
}					t_one;

int					ft_nputc(char *str, int j);
void				write_str(char *str);
void				write_c(char c, int nb);

t_lst				*parsing(char const *str);

int					everything(char c);
int					is_specifier(char c);
int					is_flag(char c, t_lst *elem);
int					is_precision(char c, t_lst *elem);
int					is_length(char c);

void				check_elem(t_lst **first);
void				what_type(t_lst *elem);

void				displaying(t_lst *list, va_list ap);

void				display_str(t_lst *list, va_list ap, t_one *one);
void				display_char(t_lst *list, int nb);

void				attributing(t_lst *lst, va_list ap, t_one *one);

void				display_number(t_lst *list, va_list ap, t_one *one);

void				display_wchar(unsigned long int nb, t_lst *list);
void				display_wstr(va_list ap, t_lst *list);

void				upper_string(char *str);
void				substring(t_lst *elem, int i);

char				*unicode_masks(char *bin);
int					ft_wcharlen(wchar_t chr);
size_t				ft_wstrlen(wchar_t *s);

int					ft_printf(char const *test, ...);

#endif
