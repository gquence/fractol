/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <gquence@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:02:16 by gquence           #+#    #+#             */
/*   Updated: 2019/08/07 00:24:27 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "cl_mod.h"

void        cl_exit(t_cl *cl_dev)
{
    clReleaseProgram(cl_dev->program);
    clReleaseKernel(cl_dev->kernel);
    clReleaseCommandQueue(cl_dev->cmd_queue);
    clReleaseContext(cl_dev->dev_context);
    clReleaseDevice(cl_dev->device_id);
    free(cl_dev->kernel_source);
}

t_cl_param  *init_clparam(t_param *param)
{
    t_cl_param  *ptr;

    if (!(ptr = (t_cl_param *)malloc(sizeof(t_cl_param))))
        return (NULL);
    ptr->max_iter = param->max_iter;
    ptr->colour = (int)param->colour;
    ptr->scale = param->scale;
    ptr->x = param->pos.x;
    ptr->y = param->pos.y;
    ptr->c_r = param->c.r;
    ptr->c_i = param->c.i;
    return (ptr);
}

int    *get_colours(t_cl *cl_dev, t_cl_param *ptr)
{
    cl_mem  input;
    cl_mem  output;
    size_t  dim[2];
    int     *arg;

    arg = (int *)malloc((WIDTH + 32) * HEIGHT * sizeof(int));
    dim[0] = WIDTH;
    dim[1] = HEIGHT;
    output = clCreateBuffer(cl_dev->dev_context, CL_MEM_WRITE_ONLY, (WIDTH + 32) * HEIGHT * sizeof(int), NULL, NULL);
    input = clCreateBuffer(cl_dev->dev_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_cl_param), ptr, NULL);
    if (!input || !output)
        return (NULL);
    cl_dev->ret_err = clSetKernelArg(cl_dev->kernel, 0, sizeof(cl_mem), &output);
    cl_dev->ret_err |= clSetKernelArg(cl_dev->kernel, 1, sizeof(cl_mem), &input);
    if (cl_dev->ret_err != CL_SUCCESS)
        return (NULL);
    cl_dev->ret_err = clEnqueueNDRangeKernel(cl_dev->cmd_queue, cl_dev->kernel, 2, NULL, dim, NULL, 0, NULL, NULL);
    if (cl_dev->ret_err != CL_SUCCESS)
        return (NULL);
    cl_dev->ret_err = clEnqueueReadBuffer(cl_dev->cmd_queue, output, CL_TRUE, 0, (WIDTH + 32) * HEIGHT * sizeof(int), arg, 0, NULL, NULL);
    if (cl_dev->ret_err != CL_SUCCESS)
        return (NULL);
    clReleaseMemObject(output);
    clReleaseMemObject(input);
    return (arg);
}

int get_img(t_param_ptr param, t_cl *cl_dev)
{
    int             *arg;
    t_cl_param      *ptr;
    t_point_2d      i;
   
    if (!(ptr = init_clparam(param)))
        return (2);
    if (!(arg = get_colours(cl_dev, ptr)))
        return (3);
    i.y = 0;
    while (i.y++ < HEIGHT)
    {
        i.x = 0;
        while (i.x++ < WIDTH)
            pixelput_img(param, &i, arg[(int)i.y * WIDTH + (int)i.x]);
    }
    free(ptr);
    free(arg);
    return (0);
}