/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 05:48:45 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:28:55 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		(*get_hit_function(int type))(
		t_object ob,
		t_ray r,
		t_record *rec,
		t_brdf *brdf)
{
	if (type == OB_SPHERE)
		return (sphere_hit);
	if (type == OB_RECT)
		return (rect_hit);
	if (type == OB_XYRECT)
		return (xyrect_hit);
	if (type == OB_XZRECT)
		return (xzrect_hit);
	if (type == OB_YZRECT)
		return (yzrect_hit);
	if (type == OB_PLANE)
		return (plane_hit);
	if (type == OB_SQUARE)
		return (square_hit);
	if (type == OB_CYLINDER)
		return (cylinder_hit);
	if (type == OB_TRIANGLE)
		return (triangle_hit);
	return (NULL);
}

t_object		*object(void *info, int type, int material, double attr)
{
	t_object	*node;

	if (!(node = malloc(sizeof(t_object))))
		return (NULL);
	node->info = info;
	node->type = type;
	node->material = material;
	node->attr = attr;
	node->hit = get_hit_function(type);
	return (node);
}
