/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 08:34:40 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:47:39 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	intersection(t_ray r, t_list *p, t_record *rec, t_brdf *brdf)
{
	int			handler;
	t_list		*p_ob;
	t_object	*node;

	handler = 0;
	p_ob = p;
	while (p_ob)
	{
		node = (t_object *)p_ob->content;
		if (node->hit(*node, r, rec, brdf))
		{
			if (node->texture == TRANSPARENT)
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

t_vec3		direct_light(t_minirt *rt, t_brdf *brdf)
{
	t_list			*p_light = rt->p_light;
	t_object		*p_ob;
	t_vec3			color = vec3(0);
	t_brdf			empty_brdf;
	while (p_light)
	{
		t_record	rec = record();
		p_ob = (t_object *)p_light->content;
		t_vec3	wi = sphere_random((t_sphere *)p_ob->info, brdf->point);
		t_ray	tmp_ray = ray(brdf->point, wi);
		p_ob->hit(*(p_ob), tmp_ray, &rec, &empty_brdf);
		if (intersection(tmp_ray, rt->p_object, &rec, &empty_brdf))
		{
			p_light = p_light->next;
			continue;
		}
		t_vec3	li = v_mul(((t_sphere *)p_ob->info)->rgb, p_ob->attr);
		double	pdf = light_pdf(p_ob, tmp_ray);
		li = v_div(li, pdf);
		t_vec3	tmp;
		if (brdf->texture == LAMBERTIAN || brdf->texture == CHECK_BOX)
			tmp = lambert_eval(*brdf, wi);
		else
			tmp = microfacet_eval(*brdf, wi);
		li = v_mul_v(li, tmp);
		color = v_add_v(color, li);
		p_light = p_light->next;
	}
	return (color);
}

t_vec3		trace(t_ray r, t_minirt *rt, int depth)
{
	if (depth <= 0)
		return (rt->ambient_rgb);

	t_brdf	brdf;
	t_record	rec;
	rec = record();

	if (!intersection(r, rt->p_object, &rec, &brdf))
		return (rt->ambient_rgb);

	if (brdf.texture == LAMBERTIAN)
	{
		lambertian(&brdf);
		t_vec3	color = direct_light(rt, &brdf);

		return (v_add_v(color, v_mul_v(trace(brdf.ray, rt, depth - 1), brdf.attenuation)));
	}
	if (brdf.texture == MICROFACET_NON_METAL || brdf.texture == MICROFACET_METAL)
	{
		microfacet(&brdf);
		t_vec3	color = direct_light(rt, &brdf);

		return (v_add_v(color, v_mul_v(trace(brdf.ray, rt, depth - 1), brdf.attenuation)));
	}
	if (brdf.texture == MIRROR)
	{
		mirror(&brdf);
		return (v_mul_v(trace(brdf.ray, rt, depth - 1), brdf.attenuation));
	}
	if (brdf.texture == TRANSPARENT)
	{
		transparent(&brdf);
		return (v_mul_v(trace(brdf.ray, rt, depth - 1), brdf.attenuation));
	}
	if (brdf.texture == CHECK_BOX)
	{
		check_box(&brdf);
		t_vec3	color = direct_light(rt, &brdf);

		return (v_add_v(color, v_mul_v(trace(brdf.ray, rt, depth - 1), brdf.attenuation)));
	}
	return (vec3(0));

}
