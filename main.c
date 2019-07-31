/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <gquence@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:53:34 by dmelessa          #+#    #+#             */
/*   Updated: 2019/07/31 16:52:48 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_event(int keycode, void *param)
{
	t_param	*pr;
	
	pr = (t_param_ptr)param;
	if (keycode == KEY_ESC || keycode == KEY_ESC_L)
		exit (1);
	else if (keycode == KEY_ONE || keycode == KEY_ONE_L)
		if (pr->colour == pink)
			pr->colour = rev_pink;
		else
			pr->colour = pink;
	else if (keycode == KEY_TWO || keycode == KEY_TWO_L)
		pr->colour = green;
	else if (keycode == KEY_THREE || keycode == KEY_THREE_L)
		pr->colour = tmp_c;
	build_fract(param);
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
		return (1);
	else if (!(ft_strcmp(av, "julia")))
		return (2);
	else if (!(ft_strcmp(av, "burning_ship")))//ИСПРАВИТЬ КАК БУДЕТ НАПИСАН ВТОРОЙ ФРАКТАЛ
		return (3);
	else
		ft_putendl("Usage /fractol \"mandelbrot\", \"julia\", \"burning_ship\"");
	return (0);
}

void	fract_init(t_param_ptr pr)
{
	if (pr->fractol == 1)
		mandelbrot_init(pr);
	else if (pr->fractol == 2)
		julia_init(pr);
	else if (pr->fractol == 3)
		bship_init(pr);
}

void	build_fract(void* ptr_pr)
{
	if (((t_param_ptr)ptr_pr)->fractol == 1)
		build_mandelbrot(ptr_pr);
	else if (((t_param_ptr)ptr_pr)->fractol == 2)
		build_julia(ptr_pr);
	else if (((t_param_ptr)ptr_pr)->fractol == 3)
		build_bship(ptr_pr);
}

int		ft_exit(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_param param;
	
	if (ac == 2)
	{
		if (!(param.fractol = choosing_fract(av[1])))
			return (0);
		mlx_initiat(&param);
		fract_init(&param);
		mlx_hook(param.win_ptr, 6, 64, mouse_julia, (void *)&param);
		mlx_hook(param.win_ptr, 17, 1L<<17, ft_exit, (void *)&param);
		mlx_key_hook(param.win_ptr, key_event, (void *)&param);
		mlx_mouse_hook(param.win_ptr, mouse_event, (void *)&param);
		mlx_loop(param.mlx_ptr);
	}
	else
		ft_putendl("Usage /fractol \"mandelbrot\", \"julia\", \"burning_ship\"");
	return (0);
}
