/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microfacet_eval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 23:13:15 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 21:35:28 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3		term1(t_brdf brdf, t_vec3 fresnel, t_vec3 wi)
{
	t_vec3			transmitted;
	t_vec3			term;

	transmitted = v_sub_v(vec3(1), fresnel);
	term = v_mul_v(transmitted, lambert_eval(brdf, wi));
	return (term);
}

static t_vec3		term2(t_brdf brdf, t_vec3 fresnel, t_dot d)
{
	t_vec3			term;

	term = v_mul(fresnel, v(brdf.attr, d.ndotwi, d.ndotwo));
	term = v_mul(term, ggx2(brdf.attr, d.ndotwh));
	term = v_mul(term, d.ndotwi);
	return (term);
}

static t_dot		dot_product(t_brdf brdf, t_vec3 wi, t_vec3 normal)
{
	t_dot			d;

	d.wodoth = clamp0_1(v_dot(brdf.wo, brdf.wh));
	d.ndotwi = clamp0_1(v_dot(normal, wi));
	d.ndotwo = clamp0_1(v_dot(normal, brdf.wo));
	d.ndotwh = clamp0_1(v_dot(normal, brdf.wh));
	return (d);
}

t_vec3				microfacet_eval(t_brdf brdf, t_vec3 wi)
{
	t_onb			uvw;
	t_vec3			normal;
	t_dot			d;
	double			costheta;
	t_vec3			fresnel;

	normal = vec(0, 1, 0);
	uvw = onb_build_from_w(normal);
	wi = onb_local(uvw, wi);
	brdf.wo = onb_local(uvw, v_inv(brdf.wo));
	brdf.wh = v_normalize(v_add_v(brdf.wo, wi));
	d = dot_product(brdf, wi, normal);
	costheta = d.wodoth;
	fresnel = fresnel_vec3(costheta, brdf.reflectance);
	return (v_add_v(term1(brdf, fresnel, wi), term2(brdf, fresnel, d)));
}
