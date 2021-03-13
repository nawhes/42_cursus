/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_brdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 03:30:30 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:18:22 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	set_face_normal(t_brdf *brdf, t_vec3 outward_normal)
{
	if (v_length(outward_normal) == 0)
		outward_normal = vec(0, 0, 1);
	brdf->front_face = v_dot(brdf->wo, outward_normal) < 0;
	if (brdf->front_face)
		return (outward_normal);
	else
		return (v_normalize(v_inv(outward_normal)));
}

static double	get_attr(t_object ob)
{
	double		attr;

	if (ob.material == MICROFACET_NON_METAL || ob.material == MICROFACET_METAL)
	{
		attr = clamp(ob.attr, 0.0001, 1);
		attr = attr * attr;
	}
	else
		attr = ob.attr;
	return (attr);
}

void			set_brdf(t_brdf *brdf, t_object ob, t_ray r, t_vec3 normal)
{
	brdf->wo = v_normalize(r.dir);
	brdf->material = ob.material;
	brdf->attr = get_attr(ob);
	brdf->normal = set_face_normal(brdf, normal);
	return ;
}

void			set_brdf2(t_brdf *brdf, t_vec3 point, t_vec3 rgb)
{
	brdf->point = point;
	brdf->albedo = rgb;
	if (brdf->material == MICROFACET_NON_METAL)
		brdf->reflectance = vec3(0.04);
	if (brdf->material == MICROFACET_METAL)
	{
		brdf->reflectance = rgb;
		brdf->albedo = vec3(0);
	}
	return ;
}
