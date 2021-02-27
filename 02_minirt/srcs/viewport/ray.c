/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:32:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/28 07:27:41 by sehpark          ###   ########.fr       */
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

static double	cosine_pdf(t_vec3 normal, t_vec3 dir)
{
	t_onb	uvw;
	uvw = onb_build_from_w(normal);
	double cosine;
	cosine = vec3_dot(vec3_unit_vector(dir), uvw.w);
	if (cosine < 0)
		return (0);
	return (cosine / PI);
}

t_vec3		direct_light(t_minirt *rt, t_ray r, t_hit_record rec)
{
	r.dir = r.dir;
	t_list			*p_light = rt->p_light;
	t_object		*p_ob;
	t_vec3			color = vec3(0, 0, 0);
	while (p_light)
	{
		t_hit_record	light_rec = hit_record();
		p_ob = (t_object *)p_light->content;
		t_vec3	l = sphere_random((t_sphere *)p_ob->info, rec.p);
		p_ob->hit(*(p_ob), ray(rec.p, l), &light_rec);
		if (intersection(ray(rec.p, l), rt->p_object, &light_rec))
		{
			p_light = p_light->next;
			continue;
		}
		t_vec3	li = vec3_mul(((t_sphere *)p_ob->info)->rgb, p_ob->attr);
		double	pdf = light_pdf_value(p_ob, ray(rec.p, l));
		/*
		if (pdf < 0.001)
		{
			p_light = p_light->next;
			continue;
		}
		*/
		double	texture_pdf = cosine_pdf(rec.normal, l);
		li = vec3_div(vec3_mul(li, texture_pdf), pdf);
		color = vec3_add(color, vec3_mul_vec3(rec.albedo, li));
		p_light = p_light->next;
	}
	return (color);
}


t_vec3		ray_color(t_ray r, t_minirt *rt, int depth)
{
	if (depth <= 0)
		return (vec3(0, 0, 0));

	t_hit_record	rec;
	rec = hit_record();

	if (!intersection(r, rt->p_object, &rec))
		return (rt->ambient_rgb);

	//분기점
//	if (rec.texture == DIFFUSE_LIGHT)
//	{
//		diffuse_light(&rec);
//		return (rec.emitted);
//	}
	if (rec.texture == LAMBERTIAN)
	{
		double	texture_pdf;
		lambertian(&rec, light_random(rt->p_light, rec.p), &texture_pdf);
		t_vec3	color = direct_light(rt, r, rec);
	//	pdf = texture_pdf * 0.5 + light_pdf(rt->p_light, rec.ray) * 0.5;

		t_vec3	ret;
	//	ret = vec3_div(vec3_mul(rec.attenuation, texture_pdf), pdf);
		ret = vec3_mul(rec.attenuation, texture_pdf);
		return (vec3_add(color, vec3_mul_vec3(ray_color(rec.ray, rt, depth - 1), ret)));
	}
	if (rec.texture == METAL)
	{
		metal(&r, &rec);
		return (vec3_mul_vec3(ray_color(rec.ray, rt, depth - 1), rec.attenuation));
	}
	if (rec.texture == DIELECTRIC)
	{
		dielectric(&r, &rec);
		return (vec3_mul_vec3(ray_color(rec.ray, rt, depth - 1), rec.attenuation));
	}
	/*
	if (rec.texture == CHECK_BOX)
	{
		double	texture_pdf;
		check_box(&rec, light_random(rt->p_light, rec.p), &texture_pdf);
	}
	*/
	return (vec3(0, 0, 0));

}
