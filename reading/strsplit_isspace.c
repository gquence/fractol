/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_isspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gquence <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:42:57 by gquence           #+#    #+#             */
/*   Updated: 2019/05/08 18:35:41 by gquence          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	ft_wc(char const *s)
{
	unsigned int wc;

	wc = 0;
	while (*s && ft_isspace(*s))
		s++;
	while (*s)
	{
		while (*s && !ft_isspace(*s))
			s++;
		wc++;
		while (*s && ft_isspace(*s))
			s++;
	}
	return (wc);
}

char				**strsplit1(char const *s)
{
	char		**p;
	const char	*estr;
	size_t		i;

	if (!s || !(p = (char **)malloc((ft_wc(s) + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (*s && ft_isspace(*s))
		s++;
	while (*s)
	{
		estr = s;
		while (*estr && !ft_isspace(*estr))
			estr++;
		*(p + i++) = ft_strsub(s, 0, estr - s);
		s = estr;
		while (*s && ft_isspace(*s))
			s++;
	}
	*(p + i) = NULL;
	return (p);
}
