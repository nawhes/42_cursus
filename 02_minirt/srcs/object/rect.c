/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/22 06:24:28 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"
#include "viewport.h"

#include "object.h"
#include <math.h>
#include <stdlib.h>

int			rect_hit(t_object ob, t_ray *r, t_hit_record *rec)
{
	t_rect	info = *((t_rect *)ob.info);
	double	t;
	double	x;
	double	y;
	t_vec3	outward_normal;

	t = (info.k - r->orig.z) / r->dir.z;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	x = r->orig.x + t * r->dir.x;
	y = r->orig.y + t * r->dir.y;
	if (x < info.x0 || x > info.x1 || y < info.y0 || y > info.y1)
		return (0);
	rec->u = (x - info.x0) / (info.x1 - info.x0);
	rec->v = (y - info.y0) / (info.y1 - info.y0);
	rec->t = t;
	outward_normal = vec3(0, 0, 1);
	
	rec->p = ray_at(*r, rec->t);
	rec->t_max = rec->t;
	rec->set_face_normal(rec, r, &outward_normal);
	if (ob.texture == LAMBERTIAN)
	{
		rec->scatter = lambertian_scatter;
		rec->emitted = vec3(0, 0, 0);
		rec->rgb = info.rgb;
	}
	if (ob.texture == METAL)
	{
		rec->scatter = metal_scatter;
		rec->emitted = vec3(0, 0, 0);
		rec->rgb = info.rgb;
	}
	if (ob.texture == DIELECTRIC)
	{
		rec->scatter = dielectric_scatter;
		rec->emitted = vec3(0, 0, 0);
		rec->rgb = info.rgb;
	}
	if (ob.texture == DIFFUSE_LIGHT)
	{
		rec->scatter = NULL;
		rec->emitted = info.rgb;
		rec->rgb = info.rgb;
	}
	if (ob.texture == CHECK_BOX)
	{
		rec->scatter = lambertian_scatter;
		rec->emitted = vec3(0, 0, 0);
		double sines;
		sines = sin(10 * rec->p.x) * sin(10 * rec->p.y) * sin(10 * rec->p.z);
		if (sines < 0)
			rec->rgb = vec3(0.2, 0.3, 0.1);
		else
			rec->rgb = vec3(0.9, 0.9, 0.9);
	}
	return (1);
}

t_rect		*rect(double x0, double x1, double y0, double y1, double k, t_vec3 rgb)
{
	t_rect		*node;

	if (!(node = malloc(sizeof(t_rect))))
		return (NULL);
	node->x0 = x0;
	node->x1 = x1;
	node->y0 = y0;
	node->y1 = y1;
	node->k = k;
	node->rgb = rgb;
	return (node);
}
