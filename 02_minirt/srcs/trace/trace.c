/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 08:34:40 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/18 05:53:16 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int			intersection(
		t_ray r,
		t_list *p,
		t_record *rec,
		t_brdf *brdf)
{
	int				handler;
	t_list			*p_ob;
	t_object		*node;

	handler = 0;
	p_ob = p;
	while (p_ob)
	{
		node = (t_object *)p_ob->content;
		if (node->hit(*node, r, rec, brdf))
			handler = 1;
		p_ob = p_ob->next;
	}
	return (handler);
}

static int			measure_light(
		t_object *p_light,
		t_minirt *rt,
		t_direct_light dl,
		t_vec3 *li)
{
	t_list			*p_ob;
	t_object		*node;
	double			pdf;

	p_ob = rt->p_object;
	sphere_hit(*(p_light), dl.ray, &dl.rec, &dl.brdf);
	while (p_ob)
	{
		node = (t_object *)p_ob->content;
		if (node->hit(*node, dl.ray, &dl.rec, &dl.brdf))
		{
			if (dl.brdf.material != TRANSPARENT)
				return (0);
			transparent(&dl.brdf);
			dl.ray = dl.brdf.ray;
			dl.rec = record();
			p_ob = rt->p_object;
			sphere_hit(*(p_light), dl.ray, &dl.rec, &dl.brdf);
			continue ;
		}
		p_ob = p_ob->next;
	}
	pdf = light_pdf(p_light, dl.ray);
	*li = v_div(((t_sphere *)p_light->info)->rgb, pdf);
	return (1);
}

t_vec3				direct_light(t_minirt *rt, t_brdf *brdf)
{
	t_list			*p_light;
	t_vec3			color;
	t_vec3			li;
	t_object		*p_ob;
	t_direct_light	dl;

	color = vec3(0);
	p_light = rt->p_light;
	while (p_light)
	{
		p_ob = (t_object *)p_light->content;
		dl.rec = record();
		dl.wi = sphere_random(p_ob->info, brdf->point);
		dl.ray = ray(brdf->point, dl.wi);
		if (measure_light(p_ob, rt, dl, &li))
		{
			if (brdf->material == LAMBERTIAN)
				li = v_mul_v(li, lambert_eval(*brdf, dl.wi));
			else
				li = v_mul_v(li, microfacet_eval(*brdf, dl.wi));
			color = v_add_v(color, li);
		}
		p_light = p_light->next;
	}
	return (color);
}

static t_vec3		brdf_sample_eval(t_minirt *rt, t_brdf *brdf)
{
	t_vec3			color;

	color = vec3(0);
	if (brdf->material == LAMBERTIAN)
		lambertian(brdf);
	if (brdf->material == MICROFACET_NON_METAL ||
			brdf->material == MICROFACET_METAL)
		microfacet(brdf);
	if (brdf->material == MIRROR)
		mirror(brdf);
	if (brdf->material == TRANSPARENT)
		transparent(brdf);
	if (brdf->material != MIRROR && brdf->material != TRANSPARENT)
		color = direct_light(rt, brdf);
	return (color);
}

t_vec3				trace(t_ray r, t_minirt *rt, int depth)
{
	t_brdf			brdf;
	t_record		rec;
	t_vec3			color;

	if (depth <= 0)
		return (rt->ambient_rgb);
	rec = record();
	if (!intersection(r, rt->p_object, &rec, &brdf))
		return (rt->ambient_rgb);
	color = brdf_sample_eval(rt, &brdf);
	return (v_add_v(color,
				v_mul_v(trace(brdf.ray, rt, depth - 1), brdf.attenuation)));
}
