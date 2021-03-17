/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microfacet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 21:07:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/18 05:58:34 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** https://github.com/rorydriscoll/RayTracer/blob/master/Source/RayTracer/Brdf/
*/

static double	reflect_probability(t_vec3 fresnel, t_vec3 albedo)
{
	double		ps;
	double		pd;
	double		prob;

	ps = v_length(fresnel);
	pd = v_length(albedo);
	prob = ps / (ps + pd);
	return (prob);
}

static t_vec3	sample(t_brdf *brdf, t_vec3 fresnel, double prob, t_onb uvw)
{
	t_vec3		pdf;
	double		ndotwi;

	if (random_double() < prob)
	{
		brdf->wi = reflect(brdf->wo, brdf->wh);
		fresnel = v_div(fresnel, prob);
		ndotwi = clamp0_1(v_dot(brdf->normal, brdf->wi));
		pdf = v_mul(fresnel, g1(brdf->attr, ndotwi));
	}
	else
	{
		brdf->wi = onb_local(uvw, random_cosine_direction());
		pdf = v_div_v(v_sub_v(vec3(1), fresnel), vec3(1.0 - prob));
		pdf = v_mul_v(pdf, brdf->albedo);
	}
	brdf->ray = ray(brdf->point, brdf->wi);
	return (pdf);
}

void			microfacet(t_brdf *brdf)
{
	t_onb		uvw;
	t_vec3		fresnel;
	double		prob;
	double		costheta;

	uvw = onb_build_from_w(brdf->normal);
	brdf->wh = onb_local(uvw, random_microfacet_direction(brdf->attr));
	costheta = clamp0_1(v_dot(v_inv(brdf->wo), brdf->wh));
	fresnel = fresnel_vec3(costheta, brdf->reflectance);
	prob = reflect_probability(fresnel, brdf->albedo);
	brdf->attenuation = sample(brdf, fresnel, prob, uvw);
	return ;
}
