/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:11:23 by gquence           #+#    #+#             */
/*   Updated: 2019/05/08 17:52:33 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_hex(const char *str)
{
	long long int	a;

	if (*str != 0 && *(str + 1) != 'x')
		return (0);
	str += 2;
	a = 0;
	while (ft_ishex((int)*str))
	{
		if (ft_islower((int)*str))
			a = a * 16 + (*str++ - 'a' + 10);
		else if (ft_islower((int)*str))
			a = a * 16 + (*str++ - 'A' + 10);
		else
			a = a * 16 + (*str++ - '0');
	}
	return (a);
}

int		ft_atoi_base(const char *str, const int base)
{
	long long int a;

	a = 0;
	while (ft_isspace((int)*str))
		str++;
	if (base != 16 && base != 10)
		return (a);
	if (base == 10)
		return (ft_atoi(str));
	if (base == 16)
		return (convert_hex(str));
	return (0);
}
