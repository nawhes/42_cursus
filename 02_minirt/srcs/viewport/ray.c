/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:32:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/21 05:33:50 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static double	cosine_pdf(t_hit_record *rec, t_ray ray)
{
	t_onb	uvw;
	uvw = onb_build_from_w(rec->normal);
	double cosine;
	cosine = vec3_dot(vec3_unit_vector(ray.dir), uvw.w);
	if (cosine < 0)
		return (0);
	return (cosine / PI);
}

static int	intersection(t_ray r, t_list *p, t_hit_record *rec)
{
	int			handler;
	t_list		*p_ob;
	t_object	*node;

	handler = 0;
	p_ob = p;
	while (p_ob)
	{
		node = (t_object *)p_ob->content;
		if (node->hit(*node, r, rec))
		{
			set_record(*node, rec);
			handler = 1;
		}
		p_ob = p_ob->next;
	}
	return (handler);
}

t_vec3		ray_color(t_ray r, t_minirt *rt, int depth)
{
	if (depth <= 0)
		return (vec3(0, 0, 0));

	t_hit_record	rec;
	rec = hit_record();

	if (!intersection(r, rt->p_object, &rec))
		return (rt->ambient_rgb);

	double	texture_pdf = 1;
	double	pdf = 1;
	//분기점
	if (rec.texture == DIFFUSE_LIGHT)
	{
		diffuse_light(&rec);
		return (rec.emitted);
	}
	if (rec.texture == LAMBERTIAN)
	{
		lambertian(&rec, light_random(rt->p_light, rec.p));
		texture_pdf = cosine_pdf(&rec, rec.ray);
		pdf = texture_pdf * 0.5 + light_pdf(rt->p_light, rec.ray) * 0.5;
	}
	if (rec.texture == METAL)
	{
		metal(&r, &rec);
	}
	if (rec.texture == DIELECTRIC)
	{
		dielectric(&r, &rec);
	}
	if (rec.texture == CHECK_BOX)
	{
		check_box(&rec, light_random(rt->p_light, rec.p));
	}

	t_vec3	ret;
	ret = vec3_mul_vec3(ray_color(rec.ray, rt, depth - 1), rec.attenuation);
	ret = vec3_mul(ret, texture_pdf);
	ret = vec3_div(ret, pdf);
	return (vec3_add(rec.emitted, ret));
}
