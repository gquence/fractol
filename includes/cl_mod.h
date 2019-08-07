/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_mod.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:39:22 by gquence           #+#    #+#             */
/*   Updated: 2019/08/07 13:39:44 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_MOD_H
# define CL_MOD_H

typedef struct	s_point_cl
{
	int x;
	int y;
}				t_point_cl;

typedef struct	s_complex_cl
{
	double	r;
	double	i;
}				t_complex_cl;

# define WIDTH_CL 800
# define HEIGHT_CL 800

#endif
