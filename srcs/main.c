/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:53:34 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/07 14:36:03 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	else if (!(ft_strcmp(av, "burning_ship")))
		return (3);
	else
		get_errmsg();
	return (0);
}

int		ft_exit(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int		build(void *param)
{
	t_param		*pr;

	pr = (t_param_ptr)param;
	get_img((t_param_ptr)param, ((t_param_ptr)param)->cl_dev);
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img, 0, 0);
	return (1);
}

int		main(int ac, char **av)
{
	t_param param;
	t_cl	cl_dev;

	if (ac == 2)
	{
		if (!(param.fractol = choosing_fract(av[1])))
			return (0);
		mlx_initiat(&param);
		cl_init(&cl_dev, "test.cl", av[1]);
		param.cl_dev = &cl_dev;
		fract_init(&param);
		mlx_hook(param.win_ptr, 6, 64, mouse_julia, (void *)&param);
		mlx_hook(param.win_ptr, 17, 1L << 17, ft_exit, (void *)&param);
		mlx_key_hook(param.win_ptr, key_event, (void *)&param);
		mlx_mouse_hook(param.win_ptr, mouse_event, (void *)&param);
		mlx_loop(param.mlx_ptr);
	}
	else
		get_errmsg();
	return (0);
}
