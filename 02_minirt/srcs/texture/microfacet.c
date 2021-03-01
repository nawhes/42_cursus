/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microfacet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 23:13:15 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 04:41:57 by sehpark          ###   ########.fr       */
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
	return (vec3(x, y, z));
}

double		fresnel(double costheta, double f0)
{
	double	x = pow(1.0 - costheta, 5.0);
	return (double_max(0.0, double_min(1.0, f0 + (1.0 - f0) * x)));
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

double		microfacet_pdf(double roughness, t_vec3 normal, t_vec3 wi, t_vec3 wo)
{
	t_onb	uvw;
	uvw = onb_build_from_v(normal);
	wi = onb_local(uvw, wi);
	wo = onb_local(uvw, wo);

	t_vec3	wh = vec3_unit_vector(vec3_add(wo, wi));
	double	a2 = roughness * roughness;
	double	costheta = vec3_dot(normal, wh);
	double	exp = (a2 - 1.0) * costheta * costheta + 1.0;
	double	d = a2 / (PI * exp * exp);
	double	ret = (d * vec3_dot(wh, normal)) / (4.0 * vec3_dot(wo, wh));
//	double	ret = (d * clamp(vec3_dot(wh, normal), 0, 1)) / (4.0 * clamp(vec3_dot(wo, wh), 0, 1));
//	if (ret >= 1 || ret <= 0)
//		printf("%f\n", ret);

	return (ret);
}

t_vec3		microfacet_eval(t_hit_record rec, t_vec3 wi, t_vec3 wo)
{
	t_onb	uvw;
	t_vec3	normal = vec3(0, 1, 0);
	uvw = onb_build_from_v(normal);
	wi = onb_local(uvw, wi);
	wo = onb_local(uvw, wo);

	t_vec3	wh = vec3_unit_vector(vec3_add(wo, wi));

	double	wodoth = clamp(vec3_dot(wo, wh), 0.0, 1.0);
	double	ndotwi = clamp(vec3_dot(normal, wi), 0.0, 1.0);
	double	ndotwo = clamp(vec3_dot(normal, wo), 0.0, 1.0);
	double	ndotwh = clamp(vec3_dot(normal, wh), 0.0, 1.0);

	double	costheta = wodoth;
	//metal
	/*
	t_vec3	f = vec3(fresnel(costheta, rec.albedo.x),
					fresnel(costheta, rec.albedo.y),
					fresnel(costheta, rec.albedo.z));
	*/
	//non-metal
	t_vec3	f = vec3(fresnel(costheta, 0.04),
					fresnel(costheta, 0.04),
					fresnel(costheta, 0.04));
	t_vec3	t = vec3_sub(vec3(1, 1, 1), f);

	t_vec3	term1 = vec3_mul_vec3(t, lambert_eval(rec, wi));
	t_vec3	term2 = vec3_mul(f, v(rec.attr, ndotwi, ndotwo));
	term2 = vec3_mul(term2, ggx2(rec.attr, ndotwh));
	term2 = vec3_mul(term2, ndotwi);
	return (vec3_add(term1, term2));
}

double		g1(double roughness, double ndotx)
{
	double	a2 = roughness * roughness;
	return (2 * ndotx / (ndotx + sqrt(a2 + (1.0 - a2) * ndotx * ndotx)));
}

void		microfacet(t_hit_record *rec, double *pdf, t_ray r_in)
{
	*pdf = 1;
	t_onb	uvw;
	t_vec3	wi;
	t_vec3	wo = vec3_unit_vector(vec3_mul(r_in.dir, -1));
	t_vec3	normal = rec->normal;

	uvw = onb_build_from_w(rec->normal);
	t_vec3	wh = onb_local(uvw, random_microfacet_direction(rec->attr));

	//pdf & sample
	double	costheta = clamp(vec3_dot(wo, wh), 0, 1);
	t_vec3	f = vec3(fresnel(costheta, rec->albedo.x),
					fresnel(costheta, rec->albedo.y),
					fresnel(costheta, rec->albedo.z));

	t_vec3	ppddff;
	double	ps = vec3_length(f);
	double	pd = vec3_length(rec->albedo);
	double	pdf2 = ps / (ps + pd);
	if (random_double() < pdf2)
	{
		wi = reflect(vec3_unit_vector(vec3_mul(wo, -1)), wh);
		rec->ray = ray(rec->p, wi);
		ppddff = (vec3_mul(vec3_div(f, pdf2), g1(rec->attr, clamp(vec3_dot(normal, wi), 0, 1))));
	}
	else
	{
		uvw = onb_build_from_w(rec->normal);
		wi = onb_local(uvw, random_cosine_direction());

		ppddff = vec3_div_vec3(vec3_sub(vec3(1, 1, 1), f), vec3(1 - pdf2, 1 - pdf2, 1 - pdf2));
		ppddff = vec3_mul_vec3(ppddff, rec->albedo);
	}

	//eval
//	rec->attenuation = microfacet_eval(*rec, wi, wo);
	rec->attenuation = vec3_mul_vec3(microfacet_eval(*rec, wi, wo), ppddff);
//	rec->attenuation = rec->albedo;
	return ;
}
