/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:02:05 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/07 13:54:12 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define FT_ABS(x) ((x >= 0) ? x : (-x))
# define PI 3.14159265359
# define RAD 0.01745329252
# define WIDTH 800
# define HEIGHT 800

typedef struct	s_point_2d
{
	double x;
	double y;
}				t_point_2d;

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

typedef struct __attribute__((packed))	s_cl_param
{
	cl_int		max_iter;
	cl_double	scale;
	cl_double	x;
	cl_double	y;
	int			colour;
	cl_double	c_r;
	cl_double	c_i;
}										t_cl_param;

typedef struct	s_cl
{
	int					ret_err;
	size_t				global;
	size_t				local;
	cl_device_id		device_id;
	cl_context			dev_context;
	cl_command_queue	cmd_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				*data;
	char				*kernel_source;
	int					kernelsource_len;
}				t_cl;

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
	int			max_iter;
	t_colours	colour;
	t_point_2d	pos;
	t_complex	c;
	double		scale;
	t_cl		*cl_dev;
}				t_param;
typedef struct s_param	*t_param_ptr;

int		cl_init(t_cl *cl_dev, char *filename, char *fractol_name);
int		key_event(int keycode, void *param);
void	fract_init(t_param_ptr pr);
int		build(void *param);
void	pixelput_img(t_param_ptr pr, t_point_2d *pos, int color);
int		mouse_event(int button, int x, int y, void *ptr_pr);
int		get_img(t_param_ptr param, t_cl *cl_dev);
void	fract_init(t_param_ptr pr);
void	bship_init(t_param_ptr pr);
void	mandelbrot_init(t_param_ptr pr);
void	julia_init(t_param_ptr pr);
int		mouse_julia(int x, int y, void *ptr_params);
void	get_errmsg(void);

# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_ZERO 29
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_NINE 25
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MULTI 67
# define KEY_SPACE 49
# define KEY_ENTER 36
# define KEY_ESC 53

# define KEY_ESC_L 65307
# define KEY_LEFT_L 65361
# define KEY_RIGHT_L 65363
# define KEY_UP_L 65362
# define KEY_DOWN_L 65364
# define KEY_PLUS_L 61
# define KEY_MINUS_L 45
# define KEY_ZERO_L 48

# define KEY_ONE_L 49
# define KEY_TWO_L 50
# define KEY_THREE_L 51

# define KEY_Q_L 113
# define KEY_W_L 119
# define KEY_E_L 101

# define KEY_A_L 97
# define KEY_S_L 115
# define KEY_D_L 100
# define KEY_F_L 102
# define KEY_G_L 103
# define KEY_J_L 106
# define KEY_K_L 107
# define KEY_L_L 108

# define KEY_U_L 117
# define KEY_I_L 105
# define KEY_O_L 111

#endif
