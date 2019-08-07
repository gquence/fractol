/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:19:30 by gquence           #+#    #+#             */
/*   Updated: 2019/08/07 14:54:54 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixelput_img(t_param_ptr pr, t_point_2d *pos, int color)
{
	if (pos->x < WIDTH && pos->y < HEIGHT)
	{
		color = mlx_get_color_value(pr->mlx_ptr, color);
		ft_memcpy(pr->img_ptr + 4 * (int)(WIDTH * pos->y + pos->x),
			&color, sizeof(int));
	}
}

void	upscale(int x, int y, t_param_ptr pr)
{
	pr->pos.x = (x / pr->scale) - (x / (pr->scale * 1.1)) + pr->pos.x;
	pr->pos.y = (y / pr->scale) - (y / (pr->scale * 1.1)) + pr->pos.y;
	pr->scale *= 1.1;
	pr->max_iter += 2;
}

void	downscale(int x, int y, t_param_ptr pr)
{
	pr->pos.x = (x / pr->scale) - (x / (pr->scale / 1.1)) + pr->pos.x;
	pr->pos.y = (y / pr->scale) - (y / (pr->scale / 1.1)) + pr->pos.y;
	pr->scale /= 1.1;
	pr->max_iter += 2;
}

int		mouse_event(int button, int x, int y, void *ptr_pr)
{
	if (button == 4)
		upscale(x, y, (t_param_ptr)ptr_pr);
	else if (button == 5)
		downscale(x, y, (t_param_ptr)ptr_pr);
	if (button == 4 || button == 5)
		build(ptr_pr);
	if (((t_param_ptr)ptr_pr)->max_iter <= 0)
		((t_param_ptr)ptr_pr)->max_iter = 0;
	return (0);
}

int		key_event(int keycode, void *param)
{
	t_param	*pr;

	pr = (t_param_ptr)param;
	if (keycode == KEY_ESC || keycode == KEY_ESC_L)
		exit(1);
	else if (keycode == KEY_ONE || keycode == KEY_ONE_L)
		if (pr->colour == pink)
			pr->colour = rev_pink;
		else
			pr->colour = pink;
	else if (keycode == KEY_TWO || keycode == KEY_TWO_L)
		pr->colour = green;
	else if (keycode == KEY_THREE || keycode == KEY_THREE_L)
		pr->colour = tmp_c;
	build(param);
	return (0);
}
