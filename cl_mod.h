#ifndef FDF_H
# define FDF_H

typedef struct	s_point_2d
{
	double x;
	double y;
}				t_point_2d;

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

typedef enum	e_colours
{
	pink = 0x0f0109,
	rev_pink = 0x09010f,
	green = 0x010f09,
	tmp_c = 0x2f1100
}				t_colours;



typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	void		*img_ptr;
	int			bits_pp;
	int			size_l;
	int			endian;
	int			fractol;
	int 		julia_mouse;
	int			max_iter;
	t_colours	colour;
	t_point_2d	pos;
	t_complex	c;
	double		scale;
}				t_param;
typedef struct s_param	*t_param_ptr;

#define WIDTH 800
#define HEIGHT 800

#endif