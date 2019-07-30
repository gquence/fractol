/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:21:08 by gquence           #+#    #+#             */
/*   Updated: 2019/07/25 18:12:38 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void		mandelbrot_init(t_param_ptr pr)
{
	pr->scale = 200;
	pr->pos.x = -2.0;
	pr->pos.y = -2.0;
	pr->max_iter = 25;
	build_mandelbrot((void *)pr);
}

void	get_color_mandelbrot(t_point_2d *pos, t_param_ptr pr)
{
	int	it;
	double	tmp;
	
	it = 0;
	pr->c.r = (double)(pos->x / pr->scale) + pr->pos.x;
	pr->c.i = (double)(pos->y / pr->scale) + pr->pos.y;
	pr->z.r = 0;
	pr->z.i = 0;
	while (it < pr->max_iter && abs_comp(pr->z) < 4)
	{
		pr->z = sum(mult(pr->z, pr->z), pr->c);
		it++;
	}
	if (it == pr->max_iter)
		pixelput_img(pr, pos, 0x000000);
	else
		pixelput_img(pr, pos, 0x0f0109 * it);
}

int		build_mandelbrot(void *param)
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
			get_color_mandelbrot(&pos, pr);
		}
	}
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img, 0, 0);
	return (1);
}
