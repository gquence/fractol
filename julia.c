/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:21:08 by gquence           #+#    #+#             */
/*   Updated: 2019/06/20 14:46:31 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_color_julia(int x, int y, int n_iter)
{
	int			res_color;
	int			i;
	t_complex	z;
	t_complex	buf;

	i = 0;
	z.r = (double)x / (double)WIDTH * 2;
	z.i = (double)y / (double)HEIGHT * 2;
	res_color = 0;
	while (i < n_iter && abs_comp(z) < 16)
	{
		buf.r = 0.1;
		buf.i = -0.66;
		z = sum(mult(z, z), buf);
		i++;
	}
	res_color = ((int)((i * 0.003) * 255));
	res_color |= ((int)((i * 0.009) * 255)) << 8;
//	res_color |= ((int)((i * 0.006) * 255)) << 16;
	return (res_color);
}

int		build_julia(int x_len, int y_len, void *param)
{
	int			x;
	int			y;
	t_param		*pr;
	int			colour;
	int			n_iter;

	pr = (t_param_ptr)param;
	x_len = x_len / 2;
	y_len = y_len / 2;
	n_iter = (y_len + x_len) / 2;
	y = -y_len;
	while (y++ < y_len)
	{
		x = -x_len;
		while (x++ < x_len)
		{
			colour = get_color_julia(x, y, n_iter);
			mlx_pixel_put(pr->mlx_ptr, pr->win_ptr, x + x_len, y + y_len, colour);
		}
	}
	return (1);
}
