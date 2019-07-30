/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:21:08 by gquence           #+#    #+#             */
/*   Updated: 2019/07/21 18:14:30 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_complex	sum(const t_complex x, const t_complex y)
{
	t_complex	result;
	
	result.r = x.r + y.r;
	result.i = x.i + y.i;
	return (result);
}

t_complex	mult(const t_complex x, const t_complex y)
{
	t_complex	result;
	
	result.r = x.r * y.r - x.i * y.i;
	result.i = 2 * x.r * y.i;
	return (result);	
}

t_complex	div_d(const t_complex x, const double y)
{
	t_complex	result;

	result.r = x.r / y;
	result.i = x.i / y;
	return (result);
}

double		abs_comp(const t_complex x)
{
	return ((double)(x.r * x.r + x.i * x.i));
}

