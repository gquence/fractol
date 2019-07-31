/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <gquence@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:21:08 by gquence           #+#    #+#             */
/*   Updated: 2019/07/31 16:52:44 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_julia(int x, int y, void *ptr_params)
{
	t_param_ptr	pr;

	pr = (t_param_ptr)ptr_params;
	if (pr->fractol == 2)
	{
		pr->c.r = x * 2 - (WIDTH / 2);
		pr->c.i = y * 2 - (WIDTH / 2);
		build_julia(ptr_params);
	}
	return (0);
}

void		julia_init(t_param_ptr pr)
{
	pr->scale = 200;
	pr->pos.x = -2.0;
	pr->pos.y = -2.0;
	pr->c.r = 0;
	pr->c.i = 1024;
	pr->max_iter = 50;
	pr->colour = green;
	build_julia((void *)pr);
}

void	get_color_julia(t_point_2d *pos, t_param_ptr pr)
{
	int			it;
	double		tmp;
	t_complex	z;
	int			max;
	
	it = 0;
	max = pr->max_iter;
	z.r = (double)(pos->x / pr->scale) + pr->pos.x;
	z.i = (double)(pos->y / pr->scale) + pr->pos.y;
	while (it < max && (z.r * z.r + z.i * z.i) < 8)
	{
		tmp = z.r;
		z.r = tmp * tmp - z.i * z.i + pr->c.r / (double)WIDTH - 0.5;
		z.i = 2 * tmp * z.i - pr->c.i / (double)WIDTH;
		it++;
	}
	if (it == max)
		pixelput_img(pr, pos, 0x000000);
	else
		pixelput_img(pr, pos, pr->colour * it);
}

int		build_julia(void *param)
{
	t_point_2d	pos;
	t_param		*pr;
	int			colour;

	pr = (t_param_ptr)param;
	pos.y = 0;
	while (pos.y++ < HEIGHT)
	{
		pos.x = 0;
		while (pos.x++ < WIDTH)
		{
			get_color_julia(&pos, pr);
		}
	}
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img, 0, 0);
	return (1);
}
