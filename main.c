/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:53:34 by dmelessa          #+#    #+#             */
/*   Updated: 2019/07/25 00:07:57 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <math.h>

int key_event(int keycode, void *param)
{
	t_param	*pr;
	
	pr = (t_param_ptr)param;	
	if (keycode == KEY_ESC || keycode == KEY_ESC_L)
		exit (1);
	return (0);
}

void	mlx_initiat(t_param_ptr params)
{
	params->mlx_ptr = mlx_init();
	params->win_ptr = mlx_new_window(params->mlx_ptr, WIDTH, HEIGHT, "Fractol");
	params->img = mlx_new_image(params->mlx_ptr, WIDTH, HEIGHT);
	params->img_ptr = mlx_get_data_addr(params->img, &(params->bits_pp),
		&(params->size_l), &(params->endian));
}

int		choosing_fract(char *av)
{
	if (!(ft_strcmp(av, "mandelbrot")))
		return (0);
	else if (!(ft_strcmp(av, "julia")))
		return (1);
	else if (!(ft_strcmp(av, "some_fract")))//ИСПРАВИТЬ КАК БУДЕТ НАПИСАН ВТОРОЙ ФРАКТАЛ
		return (-1);
	else
		ft_putendl("Usage /fractol \"mandelbrot\", \"julia\", \"some_fract\"");
	return (-1);
}
/*
void	fract_init(t_param_ptr pr)
{
	if (pr->fractol == 1)
		mandelbrot(pr);
	else if (pr->fractol == 2)
		julia(pr);
}
*/
int		ft_exit(void)
{
	exit(1);
}

int	main(int ac, char **av)
{
	t_param param;
	
	if (ac == 2)
	{/*
		if (!(param.fractol = choosing_fract(av[1])))
			return (0);
		fractol_init(param);*/
		param.fractol = 1;
		mlx_initiat(&param);
		julia_init(&param);
//		mlx_hook(param.win_ptr, 6, 64, mouse_julia, (void *)&param);
//		mlx_hook(param.win_ptr, 2, 0L, key_event, (void *)&param);
		mlx_hook(param.win_ptr, 17, 0L, ft_exit, (void *)&param);
//		mlx_mouse_hook(param.win_ptr, mouse_julia, (void *)&param);
		mlx_mouse_hook(param.win_ptr, mouse_event, (void *)&param);
		mlx_loop(param.mlx_ptr);
	}
	return (0);
}
