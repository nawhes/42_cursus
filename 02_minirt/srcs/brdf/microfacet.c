/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microfacet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 23:13:15 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 09:23:51 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3		random_microfacet_direction(double roughness)
{
	double	r1 = random_double();
	double	r2 = random_double();
	double	a2 = roughness * roughness;

	double	theta = acos(sqrt((1.0 - r1) / ((a2 - 1.0) * r1 + 1.0)));
	double	phi = 2 * PI * r2;
	double	x = sin(theta) * cos(phi);
	double	y = sin(theta) * sin(phi);
	double	z = cos(theta);
	return (vec(x, y, z));
}

double		fresnel(double costheta, double f0)
{
	double	x = pow(1.0 - costheta, 5.0);
	return (fmax(0.0, fmin(1.0, f0 + (1.0 - f0) * x)));
}

double		ggx2(double roughness, double costheta)
{
	double	a2 = roughness * roughness;
	double	exp = (a2 - 1.0) * costheta * costheta + 1.0;
	return (a2 / (PI * exp * exp));
}

double		v1(double roughness, double ndotx)
{
	double	a2 = roughness * roughness;
	return (1 / (ndotx + sqrt(a2 + (1 - a2) * ndotx * ndotx)));
}

double		v(double roughness, double ndotwi, double ndotwo)
{
	return (v1(roughness, ndotwi) * v1(roughness, ndotwo));
}

double		g1(double roughness, double ndotx)
{
	double	a2 = roughness * roughness;
	return (2 * ndotx / (ndotx + sqrt(a2 + (1.0 - a2) * ndotx * ndotx)));
}

t_vec3		microfacet_eval(t_brdf brdf, t_vec3 wi)
{
	t_onb	uvw;
	t_vec3	normal = vec(0, 1, 0);
	uvw = onb_build_from_w(normal);
	wi = onb_local(uvw, wi);
	brdf.wo = onb_local(uvw, v_inv(brdf.wo));

	brdf.wh = v_normalize(v_add_v(brdf.wo, wi));

	double	wodoth = clamp0_1(v_dot(brdf.wo, brdf.wh));
	double	ndotwi = clamp0_1(v_dot(normal, wi));
	double	ndotwo = clamp0_1(v_dot(normal, brdf.wo));
	double	ndotwh = clamp0_1(v_dot(normal, brdf.wh));

	double	costheta = wodoth;
	t_vec3	f = vec(fresnel(costheta, brdf.reflectance.x),
					fresnel(costheta, brdf.reflectance.y),
					fresnel(costheta, brdf.reflectance.z));
	t_vec3	t = v_sub_v(vec3(1), f);
	t_vec3	term1 = v_mul_v(t, lambert_eval(brdf, wi));

	t_vec3	term2 = v_mul(f, v(brdf.attr, ndotwi, ndotwo));
	term2 = v_mul(term2, ggx2(brdf.attr, ndotwh));
	term2 = v_mul(term2, ndotwi);
	return (v_add_v(term1, term2));
}

void		microfacet(t_brdf *brdf)
{
	t_vec3	pdf;
	t_onb	uvw;

	//pdf & sample
	uvw = onb_build_from_w(brdf->normal);
	brdf->wh = onb_local(uvw, random_microfacet_direction(brdf->attr));

	double	costheta = clamp0_1(v_dot(v_inv(brdf->wo), brdf->wh));
	t_vec3	f = vec(fresnel(costheta, brdf->reflectance.x),
					fresnel(costheta, brdf->reflectance.y),
					fresnel(costheta, brdf->reflectance.z));

	double	ps = v_length(f);
	double	pd = v_length(brdf->albedo);
	double	per = ps / (ps + pd);
	if (random_double() < per)
	{
		brdf->wi = reflect(v_mul(brdf->wo, -1), brdf->wh);
		pdf = (v_mul(v_div(f, per), g1(brdf->attr, clamp0_1(v_dot(brdf->normal, brdf->wi)))));
	}
	else
	{
		uvw = onb_build_from_w(brdf->normal);
		brdf->wi = onb_local(uvw, random_cosine_direction());

		pdf = v_div_v(v_sub_v(vec3(1), f), vec3(1 - per));
		pdf = v_mul_v(pdf, brdf->albedo);
	}
	brdf->ray = ray(brdf->point, brdf->wi);

	brdf->attenuation = pdf;
	return ;
}
