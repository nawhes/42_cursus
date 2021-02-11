/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:32:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/04 02:05:59 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"
#include "viewport.h"
#include "tools.h"
#include "object.h"

t_ray			ray(t_vec3 orig, t_vec3 dir)
{
	t_ray		ret;

	ret.orig = orig;
	ret.dir = dir;
	return (ret);
}

t_vec3			ray_at(t_ray a, double t)
{
	t_vec3		ret;

	ret.x = a.orig.x + t * a.dir.x;
	ret.y = a.orig.y + t * a.dir.y;
	ret.z = a.orig.z + t * a.dir.z;
	return (ret);
}

t_vec3		ray_color(t_ray r, t_minirt *rt, int depth)
{
	if (depth <= 0)
		return (vec3(0, 0, 0));

	t_hit_record	rec;
	rec = hit_record();

	int		i;
	int		handler;

	handler = 0;
	i = 0;
	t_list	*tmp_p;
	tmp_p = rt->p_object;
	while (tmp_p)
	{
		t_object	*node;
		node = (t_object *)tmp_p->content;
		if (node->hit(*node, &r, &rec))
			handler = 1;
		tmp_p = tmp_p->next;
	}
	if (handler)
	{
		t_ray scattered;
		t_vec3 attenuation;
		if (rec.scatter == NULL || !rec.scatter(&r, &rec, &attenuation, &scattered))
		{
			return (rec.emitted);
		}
		return (vec3_add(rec.emitted, vec3_mul_vec3(ray_color(scattered, rt, depth - 1), attenuation)));
	}
	
	return (rt->ambient_rgb);
}
