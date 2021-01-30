/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:32:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/22 06:38:12 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"
#include "viewport.h"
#include "tools.h"
#include "object.h"

t_ray			ray_construct(t_vec3 orig, t_vec3 dir)
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

t_vec3		ray_color(t_ray r, t_list *lst, int depth)
{
	t_vec3	unit_direction;
	double	t;
	if (depth <= 0)
		return (vec3(0, 0, 0));

	t_hit_record	rec;
	hit_record_init(&rec);

	int		i;
	int		handler;

	handler = 0;
	i = 0;
	t_list	*tmp_p;
	tmp_p = lst;
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
		return (vec3_add(rec.emitted, vec3_mul_vec3(ray_color(scattered, lst, depth - 1), attenuation)));
	}
	
	unit_direction = vec3_unit_vector(r.dir);
	t = 0.5 * (unit_direction.y + 1.0);
	//t_vec3 start = vec3_mul(vec3(1.0, 1.0, 1.0), 1.0 - t);
	//t_vec3 end = vec3_mul(vec3(0.5, 0.7, 1.0), t);
	return (vec3(0.5, 0.5, 0.5));
}
