/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 05:48:45 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/05 14:48:30 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object		*object(void *info, int type, int texture, double attr)
{
	t_object	*node;

	if (!(node = malloc(sizeof(t_object))))
		return (NULL);
	node->info = info;
	node->type = type;
	node->texture = texture;
	node->attr = attr;
	if (type == OB_SPHERE)
		node->hit = sphere_hit;
	if (type == OB_RECT)
		node->hit = rect_hit;
	if (type == OB_XYRECT)
		node->hit = xyrect_hit;
	if (type == OB_XZRECT)
		node->hit = xzrect_hit;
	if (type == OB_YZRECT)
		node->hit = yzrect_hit;
	if (type == OB_PLANE)
		node->hit = plane_hit;
	if (type == OB_SQUARE)
		node->hit = square_hit;
	if (type == OB_CYLINDER)
		node->hit = cylinder_hit;
	if (type == OB_TRIANGLE)
		node->hit = triangle_hit;
	return (node);
}
