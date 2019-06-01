/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawLine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:15:13 by gquence           #+#    #+#             */
/*   Updated: 2019/05/31 17:54:22 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	ft_swap(int *x, int *y)
{
	int	z;

	z = *x;
	*x = *y;
	*y = z;
}

void	ft_swap_d(double *x, double *y)
{
	double	z;

	z = *x;
	*x = *y;
	*y = z;
}


int	get_point_colour(int start_colour, int end_colour, int diff)
{
	int	result;
	int	r;
	int	g;
	int	b;

	if (((int)diff) == 0 || start_colour == end_colour)
		return (end_colour);
	result = 0;
	r = start_colour & 0x00ff0000;
	g = start_colour & 0x0000ff00;
	b = start_colour & 0x000000ff;

	r += ((end_colour & 0x00ff0000) - r) / diff;
	g += ((end_colour & 0x0000ff00) - g) / diff;
	b += ((end_colour & 0x000000ff) - b) / diff;

	return ((r & 0x00ff0000) | (g & 0x0000ff00) | (b & 0x000000ff));
//	return (result);
}

/*
**	рисует прямую линию паралельную одной из осей
*/

void	drawline(t_point start, t_point end, t_param par, double dx, double dy)
{
	int	colour;
	
	if (dx == 0)
	{
		if (start.coord.y > end.coord.y)
		{
			ft_swap_d(&start.coord.x, &end.coord.x);
			ft_swap_d(&start.coord.y, &end.coord.y);
			ft_swap(&start.colour, &end.colour);
		}
		colour = start.colour;
		while (start.coord.y++ <= end.coord.y)
		{
			colour = get_point_colour(colour, end.colour, dy--);
			mlx_pixel_put(par.mlx_ptr, par.win_ptr, start.coord.x, start.coord.y, colour);
		}
	}
	else if (dy == 0)
	{
		if (start.coord.x > end.coord.x)
		{
			ft_swap_d(&start.coord.x, &end.coord.x);
			ft_swap_d(&start.coord.y, &end.coord.y);
			ft_swap(&start.colour, &end.colour);
		}
		colour = start.colour;
		while (start.coord.x++ <= end.coord.x)
		{
			colour = get_point_colour(colour, end.colour, dx--);
			mlx_pixel_put(par.mlx_ptr, par.win_ptr, start.coord.x, start.coord.y, colour);
		}
	}
}

/*
**	рисует линию с коэфициентом наклона < 1
*/

void	draw_xline(t_point start, t_point end, t_param par, double dx, double dy)
{
	float	grad;
	float	intery;
	int	colour;

	if (start.coord.x > end.coord.x)
	{
		ft_swap_d(&start.coord.x, &end.coord.x);
		ft_swap_d(&start.coord.y, &end.coord.y);
		ft_swap(&start.colour, &end.colour);
	}
	colour = start.colour;
	grad = (float)dy / (float)dx;
	intery = grad + start.coord.y;
	grad = (start.coord.y > end.coord.y) ? -grad : grad;
	dx = sqrt((dx * dx + dy * dy));
	while (start.coord.x++ < end.coord.x)
	{
		colour = get_point_colour(colour, end.colour, dx--);	
		mlx_pixel_put(par.mlx_ptr, par.win_ptr, (int)start.coord.x, (int)intery, colour);
		intery += grad;
	}
}

void	draw_yline(t_point start, t_point end, t_param par, double dx, double dy)
{
	float	grad;
	float	interx;
	int	colour;

	if (start.coord.y > end.coord.y)
	{
		ft_swap_d(&start.coord.x, &end.coord.x);
		ft_swap_d(&start.coord.y, &end.coord.y);
		ft_swap(&start.colour, &end.colour);
	}
	colour = start.colour;
	grad = (float)dx / (float)dy;
	interx = grad + (double)start.coord.x;
	grad = (start.coord.x > end.coord.x) ? -grad : grad;
	dx = sqrt((dx * dx + dy * dy));
	while (start.coord.y++ < end.coord.y)
	{
		colour = get_point_colour(colour, end.colour, dx--);
		mlx_pixel_put(par.mlx_ptr, par.win_ptr, (int)interx, (int)start.coord.y, colour);
		interx += grad;
	}
}

void	draw_brline(t_point start, t_point end, void *p_params)
{
	double	dx;
	double	dy;
	t_param	params;

	params = *((t_param_ptr)p_params);
	dx = (end.coord.x > start.coord.x) ? (end.coord.x - start.coord.x) : (start.coord.x - end.coord.x);
	dy = (end.coord.y > start.coord.y) ? (end.coord.y - start.coord.y) : (start.coord.y - end.coord.y);
	if (dx == 0 || dy == 0)
	{
		drawline(start, end, params, dx, dy);
		return ;
	}
	if (dx > dy)
		draw_xline(start, end, params, dx, dy);
	else
		draw_yline(start, end, params, dx, dy);
}
