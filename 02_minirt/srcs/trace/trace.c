/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 08:34:40 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 23:57:40 by sehpark          ###   ########.fr       */
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
		{
			if (node->material == TRANSPARENT)
			{
				transparent(brdf);
				r = brdf->ray;
			}
			else
				handler = 1;
		}
		p_ob = p_ob->next;
	}
	return (handler);
}

static t_vec3		measure_light(t_brdf *brdf, t_object *p_ob, t_vec3 wi)
{
	t_vec3			li;
	double			pdf;
	t_vec3			tmp;

	li = v_mul(((t_sphere *)p_ob->info)->rgb, p_ob->attr);
	pdf = light_pdf(p_ob, ray(brdf->point, wi));
	li = v_div(li, pdf);
	if (brdf->material == LAMBERTIAN || brdf->material == CHECK_BOX)
		tmp = lambert_eval(*brdf, wi);
	else
		tmp = microfacet_eval(*brdf, wi);
	li = v_mul_v(li, tmp);
	return (li);
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
		sphere_hit(*(p_ob), dl.ray, &dl.rec, &dl.brdf);
		if (!intersection(dl.ray, rt->p_object, &dl.rec, &dl.brdf))
		{
			li = measure_light(brdf, (t_object *)p_light->content, dl.wi);
			color = v_add_v(color, li);
		}
		p_light = p_light->next;
		continue;
	}
	return (color);
}

static t_vec3		brdf_sample_eval(t_minirt *rt, t_brdf *brdf)
{
	t_vec3			color;

	color = vec3(0);
	if (brdf->material == LAMBERTIAN)
	{
		lambertian(brdf);
		color = direct_light(rt, brdf);
	}
	if (brdf->material == MICROFACET_NON_METAL ||
			brdf->material == MICROFACET_METAL)
	{
		microfacet(brdf);
		color = direct_light(rt, brdf);
	}
	if (brdf->material == MIRROR)
		mirror(brdf);
	if (brdf->material == TRANSPARENT)
		transparent(brdf);
	if (brdf->material == CHECK_BOX)
	{
		check_box(brdf);
		color = direct_light(rt, brdf);
	}
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
