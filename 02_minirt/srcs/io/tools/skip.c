/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:42:03 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 19:58:05 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		skip(char *line, int *i)
{
	while (ft_isspace(*(line + *i)))
		(*i)++;
	return ;
}

void		skip1(char *line, int *i, char c1)
{
	while (ft_isspace(*(line + *i)) || *(line + *i) == c1)
		(*i)++;
	return ;
}

void		skip2(char *line, int *i, char c1, char c2)
{
	while (ft_isspace(*(line + *i)) || *(line + *i) == c1 || *(line + *i) == c2)
		(*i)++;
	return ;
}
