/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 01:55:46 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/14 02:25:17 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minirt.h"
#include "struct.h"
#include "rt.h"

static void		parse_rt2(t_minirt *rt)
{
	if (*rt->line == 'r' && *(rt->line + 1) == 't')
		rt_rect(rt);
	else if (*rt->line == 'x' && *(rt->line + 1) == 'y')
		rt_xyrect(rt);
	else if (*rt->line == 'x' && *(rt->line + 1) == 'z')
		rt_xzrect(rt);
	else if (*rt->line == 'y' && *(rt->line + 1) == 'z')
		rt_yzrect(rt);
	else if (*rt->line == 'c' && *(rt->line + 1) == 'u')
		rt_cube(rt);
	else if (*rt->line == 'p' && *(rt->line + 1) == 'y')
		rt_pyramid(rt);
	else if (*rt->line == 'c')
		rt_camera(rt);
	else if (*rt->line == '#' || *rt->line == '\0')
		return ;
	else
		error_handle(-2, rt);
}

static void		parse_rt(t_minirt *rt)
{
	if (*rt->line == 'R')
		rt_resolution(rt);
	else if (*rt->line == 'A')
		rt_ambientlight(rt);
	else if (*rt->line == 'l')
		rt_light(rt);
	else if (*rt->line == 's' && *(rt->line + 1) == 'p')
		rt_sphere(rt);
	else if (*rt->line == 'p' && *(rt->line + 1) == 'l')
		rt_plane(rt);
	else if (*rt->line == 's' && *(rt->line + 1) == 'q')
		rt_square(rt);
	else if (*rt->line == 'c' && *(rt->line + 1) == 'y')
		rt_cylinder(rt);
	else if (*rt->line == 't' && *(rt->line + 1) == 'r')
		rt_triangle(rt);
	else
		parse_rt2(rt);
}

int				read_rt(const char *filename, t_minirt *rt)
{
	int			fd;
	int			handler;

	printf("filename : %s\n", filename);
	if ((fd = open(filename, O_RDONLY)) == -1)
		error_handle(-1, rt);
	while ((handler = get_next_line(fd, &(rt->line))) == 1)
	{
		printf("%s\n", rt->line);
		parse_rt(rt);
		free_all(&(rt->line), NULL);
	}
	printf("%s\n", rt->line);
	parse_rt(rt);
	free_all(&(rt->line), NULL);
	if (handler == -1)
		error_handle(-3, rt);
	return (0);
}
