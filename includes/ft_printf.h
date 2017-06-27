/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edeveze <edeveze@marvin42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:35:14 by edeveze           #+#    #+#             */
/*   Updated: 2017/06/27 16:50:26 by edeveze          ###   ########.fr       */
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

# include "libft.h"

typedef	enum		e_error
{
	ARGUMENT, MALLOC
}					t_error;

typedef enum		e_type
{
	EMPTY, STR, ARG_STR, INT, U_INT, WCHAR_T, WCHAR_TSTR, WIN_T, VOID, CHAR, U_CHAR,
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
	char 			*hash;
	char 			c;
	int 			dif_pre;
	int 			dif_width;
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

void	write_char(char c, int i);
char	*unsigned_long_itoa(unsigned long long n);
char	*long_itoa(intmax_t n);
void	displaying(char **saved, t_lst *list, va_list ap);

void	display_number(char **saved, t_lst *list, va_list ap, t_one *one);

void	display_str(char **saved, t_lst *list, va_list ap, t_one *one);
void	display_char(char **saved, t_lst *list, int nb);
void	display_wchar(char **saved, unsigned long int nb);
void	display_wstr(char **saved, va_list ap);

char  *bufferize(char **saved, char *buf, int nb);

#endif
