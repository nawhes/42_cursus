/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:32:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 04:39:19 by sehpark          ###   ########.fr       */
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
			if (node->texture == DIELECTRIC)
			{
				dielectric(r, rec);
				r = rec->ray;
			}
			else
			{
				set_record(*node, rec);
				handler = 1;
			}
		}
		p_ob = p_ob->next;
	}
	return (handler);
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
		t_vec3	wi = sphere_random((t_sphere *)p_ob->info, rec.p);
		p_ob->hit(*(p_ob), ray(rec.p, wi), &light_rec);
		if (intersection(ray(rec.p, wi), rt->p_object, &light_rec))
		{
			p_light = p_light->next;
			continue;
		}
		t_vec3	li = vec3_mul(((t_sphere *)p_ob->info)->rgb, p_ob->attr);
		double	pdf = light_pdf_value(p_ob, ray(rec.p, wi));
		li = vec3_div(li, pdf);
		t_vec3	tmp = lambert_eval(rec, wi);
		li = vec3_mul_vec3(li, tmp);
		color = vec3_add(color, li);
		p_light = p_light->next;
	}
	return (color);
}

t_vec3		direct_light2(t_minirt *rt, t_ray r, t_hit_record rec)
{
	r.dir = r.dir;
	t_list			*p_light = rt->p_light;
	t_object		*p_ob;
	t_vec3			color = vec3(0, 0, 0);
	t_vec3			wo = vec3_unit_vector(vec3_mul(r.dir, -1));
	while (p_light)
	{
		t_hit_record	light_rec = hit_record();
		p_ob = (t_object *)p_light->content;
		t_vec3	wi = sphere_random((t_sphere *)p_ob->info, rec.p);
		p_ob->hit(*(p_ob), ray(rec.p, wi), &light_rec);
		if (intersection(ray(rec.p, wi), rt->p_object, &light_rec))
		{
			p_light = p_light->next;
			continue;
		}
		t_vec3	li = vec3_mul(((t_sphere *)p_ob->info)->rgb, p_ob->attr);
		double	pdf = light_pdf_value(p_ob, ray(rec.p, wi));
		li = vec3_div(li, pdf);
		t_vec3	tmp = microfacet_eval(rec, wi, wo);
		li = vec3_mul_vec3(li, tmp);
		color = vec3_add(color, li);
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

	if (rec.texture == LAMBERTIAN)
	{
		lambertian(&rec);
		t_vec3	color = direct_light(rt, r, rec);

		return (vec3_add(color, vec3_mul_vec3(ray_color(rec.ray, rt, depth - 1), rec.attenuation)));
	}
	if (rec.texture == MICROFACET)
	{
		microfacet(&rec, r);
		t_vec3	color = direct_light2(rt, r, rec);

		return (vec3_add(color, vec3_mul_vec3(ray_color(rec.ray, rt, depth - 1), rec.attenuation)));
	}
	if (rec.texture == METAL)
	{
		metal(&r, &rec);
		return (vec3_mul_vec3(ray_color(rec.ray, rt, depth - 1), rec.attenuation));
	}
	if (rec.texture == DIELECTRIC)
	{
		dielectric(r, &rec);
		return (vec3_mul_vec3(ray_color(rec.ray, rt, depth - 1), rec.attenuation));
	}
	/*
	if (rec.texture == CHECK_BOX)
	{
		double	texture_pdf;
		check_box(&rec, &texture_pdf);
	}
	*/
	return (vec3(0, 0, 0));

}
