/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:54:23 by gquence           #+#    #+#             */
/*   Updated: 2019/05/08 19:04:35 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	del_pp(char ***pparr)
{
	char	**parr;

	if (!pparr || !*pparr)
		return (0);
	parr = *pparr;
	while (*parr)
	{
		ft_memdel((void **)parr);
		parr++;
	}
	parr = *pparr;
	free(parr);
	return (1);
}

void	out_arr_str(char **arr)
{
	while (*arr)
	{
		ft_putstr(*arr);
		ft_putchar('\t');
		arr++;
	}
	ft_putchar('\n');
}

void	out_arr_splited(char ***arr_splited)
{
	int counter;

	counter = 0;
	while (arr_splited[counter])
	{
		out_arr_str(arr_splited[counter]);
		counter++;
	}
}

int	get_splittedlen(char **splitted)
{
	int	result;

	result = 0;
	if (!splitted)
		return (0);
	while (*splitted)
	{
		result++;
		splitted++;
	}
	return (result);
}

void	del_arr_splited(char ****p_arrsplited)
{
	int		counter;
	char	***arr_splited;

	counter = 0;
	arr_splited = *p_arrsplited;
	while (*arr_splited)
	{
		del_pp(arr_splited);
		arr_splited++;
	}
	free(*p_arrsplited);
}

char	***splited_join(char ****p_arrsplited, char *line, int count)
{
	char	***result;
	char	***buf;
	int	len;

	buf = *p_arrsplited;
	if (!(result = (char ***)malloc(sizeof(char **) * (count + 2))))
		return (NULL);
	result[count + 1] = NULL;
	if (!(result[count] = strsplit1(line)))
			return (NULL);
	if (buf[0] && get_splittedlen(result[count]) != get_splittedlen(buf[0]))
		return (NULL);
	while (--count != -1)
		result[count] = buf[count];
	free(*p_arrsplited);
	return (result);
}

int		read_field(int fd, t_param_ptr params)
{
	char	*line;
	char	***splitted;
	int		line_count;
	int		counter1;
	int		counter2;

	line_count = 0;
	splitted = (char ***)malloc(sizeof(char **));
	*splitted = NULL;
	counter1 = 0;
	while (get_next_line(fd, &line))
	{
		if (!(splitted = splited_join(&splitted, line, line_count)))
		{
			del_arr_splited(&splitted);
			free(line);
			return (0);
		}
		if (counter1 != (counter2 = get_splittedlen(*splitted)) && counter1)
		{
			del_arr_splited(&splitted);
			free(line);
			return (0);	
		}
		counter1 = counter2;
		ft_strdel(&line);
		line_count++;
	}
	params->n_columns = get_splittedlen(*splitted);
	params->n_lines = line_count;
	params->n_elems = params->n_columns * line_count;
	if (!(params->points = convert_allpoints(splitted, line_count, (params->n_columns))))
	{
		del_arr_splited(&splitted);
		return (0);
	}
	del_arr_splited(&splitted);
	return (1);
}
/*
#include <unistd.h>
#include <fcntl.h>
int main(int ac, char **av)
{
	int fd;
	t_point *arr;
	t_param param;

	if ((fd = open(av[1], O_RDONLY)) < 0)
		return(-1);
	read_field(fd, &param);
}*/
