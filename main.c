/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:53:34 by dmelessa          #+#    #+#             */
/*   Updated: 2019/06/01 14:47:26 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <math.h>

#define PI 3.14159265359
#define RAD 0.01745329252

t_mat3 get_scaling_matrix(double c)
{
	return ((t_mat3){
					c, 0, 0,
					0, c, 0,
					0, 0, c});
}

t_mat3	matrices_multi(const t_mat3_ptr mat1, const t_mat3_ptr mat2)
{
	t_mat3 rt;

	rt.elems[0][0] = mat1->elems[0][0] * mat2->elems[0][0] +
		mat1->elems[0][1] * mat2->elems[1][0] + mat1->elems[0][2] * mat2->elems[2][0];
	rt.elems[0][1] = mat1->elems[0][0] * mat2->elems[0][1] +
		mat1->elems[0][1] * mat2->elems[1][1] + mat1->elems[0][2] * mat2->elems[2][1];
	rt.elems[0][2] = mat1->elems[0][0] * mat2->elems[0][2] +
		mat1->elems[0][1] * mat2->elems[1][2] + mat1->elems[0][2] * mat2->elems[2][2];
	rt.elems[1][0] = mat1->elems[1][0] * mat2->elems[0][0] +
		mat1->elems[1][1] * mat2->elems[1][0] + mat1->elems[1][2] * mat2->elems[2][0];
	rt.elems[1][1] = mat1->elems[1][0] * mat2->elems[0][1] +
		mat1->elems[1][1] * mat2->elems[1][1] + mat1->elems[1][2] * mat2->elems[2][1];
	rt.elems[1][2] = mat1->elems[1][0] * mat2->elems[0][2] +
		mat1->elems[1][1] * mat2->elems[1][2] + mat1->elems[1][2] * mat2->elems[2][2];
	rt.elems[2][0] = mat1->elems[2][0] * mat2->elems[0][0] +
		mat1->elems[2][1] * mat2->elems[1][0] + mat1->elems[2][2] * mat2->elems[2][0];
	rt.elems[2][1] = mat1->elems[2][0] * mat2->elems[0][1] +
		mat1->elems[2][1] * mat2->elems[1][1] + mat1->elems[2][2] * mat2->elems[2][1];
	rt.elems[2][2] = mat1->elems[2][0] * mat2->elems[0][2] +
		mat1->elems[2][1] * mat2->elems[1][2] + mat1->elems[2][2] * mat2->elems[2][2];
	return (rt);
}

t_vec3	vec_mat_multi(const t_vec3_ptr v, const t_mat3_ptr m)
{
	return ((t_vec3){
			v->x * m->elems[0][0] + v->y * m->elems[1][0] + v->z * m->elems[2][0],
			v->x * m->elems[0][1] + v->y * m->elems[1][1] + v->z * m->elems[2][1],
			v->x * m->elems[0][2] + v->y * m->elems[1][2] + v->z * m->elems[2][2]});
}

t_vec3	get_transformed(const t_vec3_ptr v)
{
	return ((t_vec3){
		(v->x + 1.0f) * X_FACTOR,
		(-v->y + 1.0f) * Y_FACTOR,
		v->z});
}

t_vec3	perspective_transforamtion(const t_vec3_ptr v)
{
	const float zInv = 1.0f / v->z;
	return ((t_vec3){
		(v->x * (double)zInv + 1.0f) * X_FACTOR,
		(-v->y * (double)zInv + 1.0f) * Y_FACTOR,
		v->z});
}

t_mat3 get_rotate_mat_z(double angle)
{
	const double sin_a = sin(angle * RAD);
	const double cos_a = cos(angle * RAD);

	return ((t_mat3) {
			cos_a,	sin_a,	0,
			-sin_a,	cos_a,	0,
			0,		0,		1});
}

t_mat3 get_rotate_mat_y(double angle)
{
	const double sin_a = sin(angle * RAD);
	const double cos_a = cos(angle * RAD);

	return ((t_mat3) {
			cos_a,	0,	-sin_a,
			0,		1,	0,
			sin_a,	0,	cos_a});
}

t_mat3 get_rotate_mat_x(double angle)
{
	const double sin_a = sin(angle * RAD);
	const double cos_a = cos(angle * RAD);

	return ((t_mat3) {
			1,	0,		0,
			0,	cos_a,	sin_a,
			0,	-sin_a,	cos_a});
}

t_vec3	rotate_x(const t_vec3_ptr v, double x)
{
	t_mat3 a;

	a = get_rotate_mat_x(x);
	return (vec_mat_multi(v, &a));
}

t_vec3	rotate_y(const t_vec3_ptr v, double x)
{
	t_mat3 a;

	a = get_rotate_mat_y(x);
	return (vec_mat_multi(v, &a));
}

t_vec3	rotate_z(const t_vec3_ptr v, double x)
{
	t_mat3 a;

	a = get_rotate_mat_z(x);
	return (vec_mat_multi(v, &a));
}

/*
** Очевидно, что для вращения всей карты лучше использовать матрицу,
** потому как вращая каждую точку отдельно придется вычислять каждый раз значения
** матриц
*/

t_mat3 get_rot_mat_xyz(double x, double y, double z)
{
	t_mat3 a = get_rotate_mat_x(x);
	t_mat3 b = get_rotate_mat_y(y);
	t_mat3 c = get_rotate_mat_z(z);
	t_mat3 pr = matrices_multi(&a, &b);
	t_mat3 r = matrices_multi(&pr, &c);
	return (r);
}

t_vec3 rotate_xyz(const t_vec3_ptr v, double x, double y, double z)
{
	t_vec3 a;
	t_mat3 b;

	b = get_rotate_mat_x(x);
	a = vec_mat_multi(v, &b);
	b = get_rotate_mat_y(y);
	a = vec_mat_multi(&a, &b);
	b = get_rotate_mat_z(z);
	a = vec_mat_multi(&a, &b);
	return (a);
}

int	draw_image(void *param, t_point *points)
{
	void *mlx_ptr = ((t_param_ptr)param)->mlx_ptr;
	void *win_ptr = ((t_param_ptr)param)->win_ptr;
	int		i;

	i = 0;
	while (points[i + 1].coord.x != (double)POINT_END)
	{
		if (((i + 1) % (((t_param_ptr)param)->n_columns)))
			draw_brline(points[i], points[i + 1], param);
		if ((i + (((t_param_ptr)param)->n_columns)) < ((t_param_ptr)param)->n_elems)
			draw_brline(points[i], points[i + ((t_param_ptr)param)->n_columns], param);
		i++;
	}
	return (1);
}

int key_event(int keycode, void *param)
{
	t_point *points;
	t_mat3	a;
	t_mat3	b;
	t_param	*pr;
	
	pr = (t_param_ptr)param;	
	if (!(points = (t_point *)malloc(sizeof(t_point) * (((t_param_ptr)param)->n_elems + 1))))
			exit(0);
	points[((t_param_ptr)param)->n_elems].coord.x = POINT_END;
	if (keycode == KEY_ESC || keycode == KEY_ESC_L)//выход из программы
	{
		mlx_destroy_window(pr->mlx_ptr, pr->win_ptr);
		free(pr->points);
		exit (0);	
	}
	/*
	**управление инвертированное, потому значения противоположны привычному расположению клавиш
	**это было сделано для удобства использования
	*/
	if (keycode == KEY_Q || keycode == KEY_Q_L)
		pr->angle_z += 5;
	if (keycode == KEY_E || keycode == KEY_E_L)
		pr->angle_z -= 5;
	if (keycode == KEY_W || keycode == KEY_W_L)
		pr->angle_x += 5;
	if (keycode == KEY_S || keycode == KEY_S_L)
		pr->angle_x -= 5;	
	if (keycode == KEY_A || keycode == KEY_A_L)
		pr->angle_y += 5;
	if (keycode == KEY_D || keycode == KEY_D_L)
		pr->angle_y -= 5;
	if (keycode == KEY_PLUS || keycode == KEY_PLUS_L)//увеличение изображения
		pr->scaling += 0.05;
	if (keycode == KEY_MINUS || keycode == KEY_MINUS_L)//уменьшение изображения
		pr->scaling -= 0.05;
	if (keycode == KEY_ONE || keycode == KEY_ONE_L)//изометрическая проекция
	{
		pr->angle_x = -26.565;
		pr->angle_y = 26.565;
		pr->angle_z = -10;
	}
	if (keycode == KEY_J || keycode == KEY_J_L)//вид сверху
	{
		pr->angle_x = -90;
		pr->angle_y = 0;
		pr->angle_z = 0;
	}
	if (keycode == KEY_U || keycode == KEY_U_L)//отражение по оси X
		pr->angle_x += 180;
	if (keycode == KEY_K || keycode == KEY_K_L)//вид справа
	{
		pr->angle_x = 0;
		pr->angle_y = 90;
		pr->angle_z = 0;
	}
	if (keycode == KEY_I || keycode == KEY_I_L)//отражение по оси Y
		pr->angle_y += 180;
	if (keycode == KEY_L || keycode == KEY_L_L)//вид спереди
	{
		pr->angle_x = 0;
		pr->angle_y = 0;
		pr->angle_z = 0;
	}
	if (keycode == KEY_O || keycode == KEY_O_L)//отражение по оси Z
		pr->angle_z +=180;
	if (keycode == KEY_ZERO || keycode == KEY_ZERO_L)
		pr->scaling = 1;
	a = get_rot_mat_xyz(pr->angle_x, pr->angle_y, pr->angle_z);//получение матрицы поворота
	b = get_scaling_matrix(pr->scaling);//получение матрицы растяжения
	for (int i = 0; i < ((t_param_ptr)param)->n_elems; i++)
	{
		points[i].coord = vec_mat_multi(&(((t_param_ptr)param)->points[i].coord),&a);
		points[i].coord = vec_mat_multi(&(points[i].coord), &b);
		points[i].coord = get_transformed(&(points[i].coord));//приведение к экранным координатам
		points[i].colour = ((t_param_ptr)param)->points[i].colour;
	}
	mlx_clear_window(((t_param *)param)->mlx_ptr, ((t_param *)param)->win_ptr);
	draw_image(param, points);
	free(points);
//	ft_putnbr(keycode);
//	ft_putchar('\n');
	return (0);
}

#include <fcntl.h>

int	main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_param param;
	int		fd;
	char	*name;
	char	*msg = "Error! You entered the empty!";
	int	flag = 0;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "FDF");
	param.mlx_ptr = mlx_ptr;
	param.win_ptr = win_ptr;
	param.scaling = 1;
	build_mandelbrot(WIDTH, HEIGHT, (void *)&param);
//	mlx_key_hook(win_ptr, key_event, (void *)&param);//отлавливание нажатий на клавиатуру и мышь
	mlx_loop(mlx_ptr);

	return (0);
}
