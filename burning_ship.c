#include "fdf.h"

void		bship_init(t_param_ptr pr)
{
	pr->scale = 200;
	pr->pos.x = -2.4;
	pr->pos.y = -2.4;
	pr->max_iter = 25;
	pr->colour = pink;
	build_bship((void *)pr);
}

void	get_color_bship(t_point_2d *pos, t_param_ptr pr)
{
	int			it;
	double		tmp;
	t_complex	z;
	int			max;
	
	it = 0;
	max = pr->max_iter;
	z.r = 0;
	z.i = 0;
	pr->c.r = (double)(pos->x / pr->scale) + pr->pos.x;
	pr->c.i = (double)(pos->y / pr->scale) + pr->pos.y;
	while (it < max && (z.r * z.r + z.i * z.i) < 8)
	{
		tmp = z.r;
		z.r = tmp * tmp - z.i * z.i + pr->c.r;
		z.i = fabs(2 * tmp * z.i) + pr->c.i;
		it++;
	}
	if (it == max)
		pixelput_img(pr, pos, 0x000000);
	else
		pixelput_img(pr, pos, pr->colour * it);
}

int		build_bship(void *param)
{
	t_point_2d	pos;
	t_param		*pr;
	int			colour;

	pr = (t_param_ptr)param;
//	get_img(pr, pr->cl_dev);
	pos.y = 0;
	while (pos.y++ < HEIGHT)
	{
		pos.x = 0;
		while (pos.x++ < WIDTH)
		{
			get_color_bship(&pos, pr);
		}
	}
	mlx_put_image_to_window(pr->mlx_ptr, pr->win_ptr, pr->img, 0, 0);
	return (1);
}
