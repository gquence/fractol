/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:43:48 by gquence           #+#    #+#             */
/*   Updated: 2019/05/08 18:37:25 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

# include "../fdf.h"
# include "libft.h"

# define TOP_BORDER 0.95
# define POINT_END -101
# define FT_ABS(x) ((x >= 0) ? x : (-x))

int		read_field(int fd, t_param_ptr params);
char		**strsplit1(char const *s);
int		normalize_arr_double(t_point *arr, int count);
t_point		*convert_allpoints(char ***splitted, int rows, int columns);

#endif
