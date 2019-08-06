#include "cl_mod.h"

typedef struct __attribute__((packed))	s_cl_param
{
	int			max_iter;
	double		scale;
	double		x;
	double		y;
	int         colour;
	t_complex	c;
	double		c_r;
	double		c_i;
}										t_cl_param;

__kernel void mandelbrot(__global int *img_ptr, __global const t_cl_param *p_params)
{
    t_point		pos;
    int			it;
	double		tmp;
	t_complex	z;
	int			max;
    t_complex   c;

    pos.y = get_global_id(0);
    pos.x = get_global_id(1);
    //printf("x=%f y=%f sc=%f col=%x max=%d,", p_params->x, p_params->y, p_params->scale, p_params->colour, p_params->max_iter);
    if (pos.y >= 0 && pos.x >= 0 && pos.y < WIDTH && pos.x < WIDTH)
    {
	    it = 0;
	    c.r = ((double)pos.x / (double)(p_params->scale)) + (double)(p_params->x);
	    c.i = ((double)pos.y / (double)(p_params->scale)) + (double)(p_params->y);
	    z.r = 0;
	    z.i = 0;
	    max = p_params->max_iter;
		//printf("%d %d\t", get_global_size(0), get_global_size(1));
		//printf("x=%d y=%d, ", pos.x, pos.y);
	    while (it < max && (z.r * z.r + z.i * z.i) < 4)
	    {
	    	tmp = z.r;
	    	z.r = tmp * tmp - z.i * z.i + c.r;
	    	z.i = 2 * tmp * z.i - c.i;
	    	it++;
            //printf("%d %d\t", it, max);
            //printf("%f");
            //printf("%f ", z.r * z.r + z.i * z.i);
            //printf("%d %d ", img_ptr[(int)(WIDTH * pos.y + pos.x)], max, it);
	    }
	    if (it == max)
            img_ptr[(int)(WIDTH * pos.y + pos.x)] = 0x000000;
	    else
            img_ptr[(int)(WIDTH * pos.y + pos.x)] = (int)p_params->colour * it;
    	//printf("%f ", z.r * z.r + z.i * z.i);
        //printf("%d ", it);
    }
}

__kernel void julia(__global int *img_ptr, __global const t_cl_param *p_params)
{
    t_point		pos;
    int			it;
	double		tmp;
	t_complex	z;
	int			max;

    pos.y = get_global_id(0);
    pos.x = get_global_id(1);
    //printf("x=%f y=%f sc=%f col=%x max=%d,", p_params->x, p_params->y, p_params->scale, p_params->colour, p_params->max_iter);
    if (pos.y >= 0 && pos.x >= 0 && pos.y < WIDTH && pos.x < WIDTH)
    {
	    it = 0;
	    max = p_params->max_iter;
		//printf("%d %d\t", get_global_size(0), get_global_size(1));
		//printf("x=%d y=%d, ", pos.x, pos.y);
		z.r = ((double)pos.x / p_params->scale) + p_params->x;
		z.i = ((double)pos.y / p_params->scale) + p_params->y;
		while (it < max && (z.r * z.r + z.i * z.i) < 8)
		{
			tmp = z.r;
			z.r = tmp * tmp - z.i * z.i + p_params->c_r / (double)WIDTH - 0.5;
			z.i = 2 * tmp * z.i - p_params->c_i / (double)WIDTH;
			it++;
            //printf("%d %d\t", it, max);
            //printf("%f");
            //printf("%f ", z.r * z.r + z.i * z.i);
            //printf("%d %d ", img_ptr[(int)(WIDTH * pos.y + pos.x)], max, it);
	    }
	    if (it == max)
            img_ptr[(int)(WIDTH * pos.y + pos.x)] = 0x000000;
	    else
            img_ptr[(int)(WIDTH * pos.y + pos.x)] = (int)p_params->colour * it;
    	//printf("%f ", z.r * z.r + z.i * z.i);
        //printf("%d ", it);
    }
}


__kernel void burning_ship(__global int *img_ptr, __global const t_cl_param *p_params)
{
    t_point		pos;
    int			it;
	double		tmp;
	t_complex	z;
	int			max;
    t_complex   c;

    pos.y = get_global_id(0);
    pos.x = get_global_id(1);
    //printf("x=%f y=%f sc=%f col=%x max=%d,", p_params->x, p_params->y, p_params->scale, p_params->colour, p_params->max_iter);
    if (pos.y >= 0 && pos.x >= 0 && pos.y < WIDTH && pos.x < WIDTH)
    {
	    it = 0;
	    c.r = ((double)pos.x / (double)(p_params->scale)) + (double)(p_params->x);
	    c.i = ((double)pos.y / (double)(p_params->scale)) + (double)(p_params->y);
	    z.r = 0;
	    z.i = 0;
	    max = p_params->max_iter;
		//printf("%d %d\t", get_global_size(0), get_global_size(1));
		//printf("x=%d y=%d, ", pos.x, pos.y);
	    while (it < max && (z.r * z.r + z.i * z.i) < 8)
	    {
	    	tmp = z.r;
	    	z.r = tmp * tmp - z.i * z.i + c.r;
	    	z.i = fabs(2 * tmp * z.i) + c.i;
	    	it++;
            //printf("%d %d\t", it, max);
            //printf("%f");
            //printf("%f ", z.r * z.r + z.i * z.i);
            //printf("%d %d ", img_ptr[(int)(WIDTH * pos.y + pos.x)], max, it);
	    }
	    if (it == max)
            img_ptr[(int)(WIDTH * pos.y + pos.x)] = 0x000000;
	    else
            img_ptr[(int)(WIDTH * pos.y + pos.x)] = (int)p_params->colour * it;
    	//printf("%f ", z.r * z.r + z.i * z.i);
        //printf("%d ", it);
    }
}
