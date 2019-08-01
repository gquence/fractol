/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <gquence@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:19:30 by gquence           #+#    #+#             */
/*   Updated: 2019/08/01 07:20:54 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    pixelput_img(t_param_ptr pr, t_point_2d *pos, int color)
{
    if (pos->x < WIDTH && pos->y < HEIGHT)
    {
        color = mlx_get_color_value(pr->mlx_ptr, color);
        ft_memcpy(pr->img_ptr + 4 * (int)(WIDTH * pos->y + pos->x),
            &color, sizeof(int));
    }
}

void    upscale(int x, int y, t_param_ptr pr)
{
    pr->pos.x = (x / pr->scale) - (x / (pr->scale * 1.1)) + pr->pos.x;
    pr->pos.y = (y / pr->scale) - (y / (pr->scale * 1.1)) + pr->pos.y;
    pr->scale *= 1.1;
    pr->max_iter++;
}

void    downscale(int x, int y, t_param_ptr pr)
{
    pr->pos.x = (x / pr->scale) - (x / (pr->scale / 1.1)) + pr->pos.x;
    pr->pos.y = (y / pr->scale) - (y / (pr->scale / 1.1)) + pr->pos.y;
    pr->scale /= 1.1;
    pr->max_iter--;
}

int     mouse_event(int button, int x, int y, void *ptr_pr)
{
    if (button == 4)
        upscale(x, y, (t_param_ptr)ptr_pr);
    else if (button == 5)
        downscale(x, y, (t_param_ptr)ptr_pr);
 //   printf("x = %f, y = %f\n", ((t_param_ptr)ptr_pr)->pos.x, ((t_param_ptr)ptr_pr)->pos.y);
    if (button == 4 || button == 5)
        build_fract(ptr_pr);
    if (((t_param_ptr)ptr_pr)->max_iter <= 0)
        fract_init(ptr_pr);        
    return (0);
}
