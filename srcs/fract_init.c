/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:21:08 by gquence           #+#    #+#             */
/*   Updated: 2019/08/07 16:06:44 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fract_init(t_param_ptr pr)
{
	if (pr->fractol == 1)
		mandelbrot_init(pr);
	else if (pr->fractol == 2)
		julia_init(pr);
	else if (pr->fractol == 3)
		bship_init(pr);
}

void	mandelbrot_init(t_param_ptr pr)
{
	pr->scale = 200;
	pr->pos.x = -2.0;
	pr->pos.y = -2.0;
	pr->max_iter = 25;
	pr->colour = pink;
	build((void *)pr);
}

void	bship_init(t_param_ptr pr)
{
	pr->scale = 200;
	pr->pos.x = -2.4;
	pr->pos.y = -2.4;
	pr->max_iter = 25;
	pr->colour = tmp_c;
	build((void *)pr);
}

int		mouse_julia(int x, int y, void *ptr_params)
{
	t_param_ptr	pr;

	pr = (t_param_ptr)ptr_params;
	if (pr->fractol == 2)
	{
		pr->c.r = (double)(x * 2 - (WIDTH / 2));
		pr->c.i = (double)(y * 2 - HEIGHT);
		build(ptr_params);
	}
	return (0);
}

void	julia_init(t_param_ptr pr)
{
	pr->scale = 200;
	pr->pos.x = -2.0;
	pr->pos.y = -2.0;
	pr->c.r = 0;
	pr->c.i = 1024;
	pr->max_iter = 50;
	pr->colour = green;
	build((void *)pr);
}
