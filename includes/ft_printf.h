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

typedef struct		s_lst
{
    struct s_lst	*next;
    int				type;
    char			*arg;
    // int				nb;
}					t_lst;

t_lst *parsing(char *str);

# endif
