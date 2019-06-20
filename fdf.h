/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:02:05 by dmelessa          #+#    #+#             */
/*   Updated: 2019/06/20 14:36:48 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define POINT_END -101

typedef struct	s_point_2d
{
	int x;
	int y;
}				t_point_2d;

# define WIDTH 1300
# define HEIGHT 1300

enum {
	x_factor = WIDTH >> 1,
	y_factor = HEIGHT >> 1
};

# define X_FACTOR (float)x_factor
# define Y_FACTOR (float)y_factor

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;
typedef struct s_vec3 *t_vec3_ptr;

typedef struct	s_point
{
	t_vec3	coord;
	int		colour;
}				t_point;
typedef struct s_point	*t_point_ptr;

typedef struct	s_mat3
{
	double	elems[3][3];
}				t_mat3;
typedef struct s_mat3	*t_mat3_ptr;

typedef struct	s_param
{
	void	*win_ptr;
	void	*mlx_ptr;
	t_point	*points;
	double	scaling;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	int	n_columns;
	int	n_lines;
	int	n_elems;
}				t_param;
typedef struct s_param	*t_param_ptr;
void		draw_brline(t_point start, t_point end, void *p_params);

# include "libft.h"

# define TOP_BORDER 0.95
# define POINT_END -101
# define FT_ABS(x) ((x >= 0) ? x : (-x))

int		read_field(int fd, t_param_ptr params);
char		**strsplit1(char const *s);
int		normalize_arr_double(t_point *arr, int count);
t_point		*convert_allpoints(char ***splitted, int rows, int columns);

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

t_complex	sum(const t_complex x, const t_complex y);
t_complex	mult(const t_complex x, const t_complex y);
double		abs_comp(const t_complex x);
int			build_mandelbrot(int x_len, int y_len, void *param);
int			build_julia(int x_len, int y_len, void *param);

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
