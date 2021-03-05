/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_brdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 03:30:30 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/06 03:51:45 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_albedo(t_brdf *brdf, t_object ob)
{
	t_vec3	albedo;

	if (ob.type == OB_SPHERE)
		albedo = ((t_sphere *)ob.info)->rgb;
	else if (ob.type == OB_XYRECT)
		albedo = ((t_xyrect *)ob.info)->rgb;
	else if (ob.type == OB_XZRECT)
		albedo = ((t_xzrect *)ob.info)->rgb;
	else if (ob.type == OB_YZRECT)
		albedo = ((t_yzrect *)ob.info)->rgb;
	else if (ob.type == OB_PLANE)
		albedo = ((t_plane *)ob.info)->rgb;
	else if (ob.type == OB_SQUARE)
		albedo = ((t_square *)ob.info)->rgb;
	else if (ob.type == OB_CYLINDER)
		albedo = ((t_cylinder *)ob.info)->rgb;
	else if (ob.type == OB_TRIANGLE)
		albedo = ((t_triangle *)ob.info)->rgb;
	else
		albedo = vec3(1);
	if (ob.texture == MICROFACET_NON_METAL)
		brdf->reflectance = vec3(0.04);
	if (ob.texture == MICROFACET_METAL)
	{
		brdf->reflectance = albedo;
		albedo = vec3(0);
	}
	return (albedo);
}
	
static t_vec3	set_face_normal(t_brdf *brdf, t_vec3 outward_normal)
{
	brdf->front_face = v_dot(brdf->wo, outward_normal) < 0;
	if (brdf->front_face)
		return (outward_normal);
	else
		return (v_normalize(v_inv(outward_normal)));
}

static double	get_attr(t_object ob)
{
	double		attr;
	if (ob.texture == MICROFACET_NON_METAL || ob.texture == MICROFACET_METAL)
	{
		attr = clamp(ob.attr, 0.0001, 1);
		attr = attr * attr;
	}
	else
		attr = ob.attr;
	return (attr);
}

void		set_brdf(t_brdf *brdf, t_object ob, t_ray r, t_vec3 normal)
{
	brdf->wo = v_normalize(r.dir);
	brdf->texture = ob.texture;
	brdf->attr = get_attr(ob);
	brdf->albedo = get_albedo(brdf, ob);
	brdf->normal = set_face_normal(brdf, normal);
	return ;
}

void		set_brdf2(t_brdf *brdf, t_vec3 point)
{
	brdf->point = point;
	return ;
}
