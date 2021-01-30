/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 01:55:46 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 22:58:31 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "io.h"
#include "struct.h"
#include "rt.h"
#include "tools.h"

static void	parse_rt(t_minirt *rt)
{
	if (*rt->line == 'R')
		rt_resolution(rt);
	else if (*rt->line == 'A')
		rt_ambientlight(rt);
	else if (*rt->line == 'c')
		rt_camera(rt);
	else if (*rt->line == 'l')
		rt_light(rt);
	else if (*rt->line == 's' || *(rt->line + 1) == 'p')
		rt_sphere(rt);
/*
	else if (*rt->line == 'p' || *(rt->line + 1) == 'l')
		rt_plane(rt);
	else if (*rt->line == 'c' || *(rt->line + 1) == 'y')
		rt_cylinder(rt);
	else if (*rt->line == 't' || *(rt->line + 1) == 'r')
		rt_triangle(rt);
*/
	else if (*rt->line == 'r')
		rt_rect(rt);
	else if (*rt->line == '#' || *rt->line == '\0')
		return ;
	else
		error_handle(-2, rt);
}
/*
	
	double	aspect_ratio;

	t_list	*node;
	aspect_ratio = 3.0 / 2.0;

	//viewport
	rt->p_viewport = NULL;
	t_viewport	*p_viewport;

	p_viewport = viewport_init(vec3(0, 0, 5), vec3(0, 0, 0), 50, aspect_ratio);
	node = ft_lstnew((void *)p_viewport);
	ft_lstadd_back(&(rt->p_viewport), node);

	//object
	t_object	*p_object;
	rt->p_object = NULL;

	p_object = object((void *)sphere(vec3(-1, 1, 0), 1, vec3(0.1, 0.2, 0.5)), T_SPHERE, LAMBERTIAN);
	node = ft_lstnew((void *)p_object);
	ft_lstadd_back(&(rt->p_object), node);

	p_object = object((void *)rect(1, 2, 1, 2, 0, vec3(0.4, 0.2, 0.1)), T_RECT, DIFFUSE_LIGHT);
	node = ft_lstnew((void *)p_object);
	ft_lstadd_back(&(rt->p_object), node);

	p_object = object((void *)sphere(vec3(0, 0, 0), 1, vec3(0.7, 0.6, 0.5)), T_SPHERE, LAMBERTIAN);
	node = ft_lstnew((void *)p_object);
	ft_lstadd_back(&(rt->p_object), node);

	//image
	rt->p_image = NULL;
	t_image	*p_image;

	p_image = image_init(1200, (int)(1200 / aspect_ratio));
	node = ft_lstnew((void *)p_image);
	ft_lstadd_back(&(rt->p_image), node);
*/

int			read_rt(const char *filename, t_minirt *rt)
{
	int		fd;
	int		handler;

	printf("filename : %s\n",filename);
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
		error_handle(-1, rt);
	return (0);
}
