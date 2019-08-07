/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:26:25 by gquence           #+#    #+#             */
/*   Updated: 2019/08/07 13:29:25 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	oclloadprogsource(const char *filename, t_cl *cl_dev)
{
	int		fd;
	char	*line;
	char	*buf;

	if (!filename || !*filename)
		return (0);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (0);
	cl_dev->kernel_source = ft_strnew(0);
	while (get_next_line(fd, &buf))
	{
		line = ft_strjoin(buf, "\n");
		ft_strdel(&buf);
		buf = ft_strjoin(cl_dev->kernel_source, line);
		ft_strdel(&line);
		ft_strdel(&(cl_dev->kernel_source));
		cl_dev->kernel_source = buf;
	}
	cl_dev->kernelsource_len = strlen(cl_dev->kernel_source);
	return (1);
}

int	get_deviceattr(t_cl *ptr_dev)
{
	cl_platform_id	*platforms;
	cl_uint			platform_count;
	int				ret_err;

	clGetPlatformIDs(0, NULL, &platform_count);
	if (!platform_count)
		return (1);
	platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) *
		(int)platform_count);
	clGetPlatformIDs(platform_count, platforms, NULL);
	ret_err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 1,
		&(ptr_dev->device_id), NULL);
	ptr_dev->dev_context = clCreateContext(0, 1, &(ptr_dev->device_id),
		NULL, NULL, &ret_err);
	free(platforms);
	return (0);
}

int	get_program(t_cl *ptr_dev, char *filename)
{
	ptr_dev->cmd_queue = clCreateCommandQueue(ptr_dev->dev_context,
		ptr_dev->device_id, 0, &ptr_dev->ret_err);
	if (!ptr_dev->cmd_queue)
		return (1);
	if (!oclloadprogsource(filename, ptr_dev))
		return (2);
	ptr_dev->program = clCreateProgramWithSource(ptr_dev->dev_context, 1,
		(const char **)&ptr_dev->kernel_source, NULL, &ptr_dev->ret_err);
	if (!ptr_dev->program)
		return (3);
	return (0);
}

int	cl_init(t_cl *cl_dev, char *filename, char *fractol_name)
{
	int	ret_err;

	if (get_deviceattr(cl_dev))
		return (1);
	if ((ret_err = get_program(cl_dev, filename)))
		return (2);
	cl_dev->ret_err = clBuildProgram(cl_dev->program,
		0, NULL, "-I ./", NULL, NULL);
	if (!cl_dev->program)
		return (3);
	cl_dev->kernel = clCreateKernel(cl_dev->program,
		fractol_name, &cl_dev->ret_err);
	if (cl_dev->ret_err != CL_SUCCESS)
		return (4);
	cl_dev->global = (WIDTH + 32) * HEIGHT * sizeof(int);
	return (0);
}
