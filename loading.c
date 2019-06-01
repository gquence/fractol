/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:21:08 by gquence           #+#    #+#             */
/*   Updated: 2019/06/01 14:51:22 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

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

double		abs_comp(const t_complex x)
{
	return ((double)(x.r * x.r + x.i * x.i));
}

int			get_color_mandel(int x, int y, int x_hlen, int y_hlen)
{
	int			res_color;
	int			i;
	t_complex	z;
	t_complex	buf;
	int			n_iter;

	i = 0;
	z.r = 0;
	z.i = 0;
	res_color = 0;
	n_iter = (y_hlen + x_hlen) / 4;
	while (i < n_iter && abs_comp(z) < 16)
	{
		buf.r = (x - x_hlen) / 180.0;
		buf.i = (y - y_hlen) / 180.0;
		z = sum(mult(z, z), buf);
		i++;
	}
	res_color = ((int)((i * 0.003 + 0.3) * 255));
	res_color |= ((int)((i * 0.009 + 0.2) * 255)) << 8;
	res_color |= ((int)((i * 0.006 + 0.1) * 255)) << 16;
	return (res_color);
	
}

int		build_mandelbrot(int x_len, int y_len, void *param)
{
	int			x;
	int			y;
	int			i;
	t_param		*pr;
	int			colour;

	pr = (t_param_ptr)param;
	y = 0;
	while (y++ < y_len)
	{
		x = 0;
		while (x++ < x_len)
		{
			colour = get_color_mandel(x, y, x_len / 2, y_len / 2);
			mlx_pixel_put(pr->mlx_ptr, pr->win_ptr, x, y, colour);
		}
	}
	return (1);
}
