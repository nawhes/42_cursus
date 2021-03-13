/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_brdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 03:30:30 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 21:42:08 by sehpark          ###   ########.fr       */
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

void			set_brdf(t_brdf *brdf, t_ray r, t_vec3 normal, t_vec3 point)
{
	brdf->wo = v_normalize(r.dir);
	brdf->normal = set_face_normal(brdf, normal);
	brdf->point = point;
	return ;
}

void			set_brdf2(t_brdf *brdf, t_object ob, t_vec3 rgb)
{
	brdf->material = ob.material;
	brdf->attr = ob.attr;
	brdf->albedo = rgb;
	apply_texture(ob.texture, brdf);
	if (brdf->material == MICROFACET_NON_METAL)
	{
		brdf->attr = clamp(ob.attr, 0.0001, 1);
		brdf->attr = brdf->attr * brdf->attr;
		brdf->reflectance = vec3(0.04);
	}
	if (brdf->material == MICROFACET_METAL)
	{
		brdf->attr = clamp(ob.attr, 0.0001, 1);
		brdf->attr = brdf->attr * brdf->attr;
		brdf->reflectance = brdf->albedo;
		brdf->albedo = vec3(0);
	}
	return ;
}
