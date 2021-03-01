/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microfacet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 23:13:15 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/01 10:42:36 by sehpark          ###   ########.fr       */
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

double		ggx(t_vec3 wh, t_vec3 wo, t_vec3 normal, double roughness)
{
	t_vec3	wh = vec3_unit_vector(vec3_add(wi, wo));
	double	costheta = vec3_dot(normal, wh);
	return (a2 / (PI * exp * exp));
}

double		smithggx(t_vec3	wo, t_vec3 normal, double roughness)
{
	double	a = roughness * roughness;
	double	a2 = a * a;
	double	ndotwo = vec3_dot(normal, wo);
	return ((2.0 * ndotwo) / (ndotwo + sqrt(a2 + (1.0 - a2) * ndotwo * ndotwo)));
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
	double	costheta = vec3_dot(wi, wh);
	if (wi.y <= 0 || costheta <= 0)
		return (vec3(1, 1, 1));
	t_vec3	f = vec3(fresnel(costheta, rec.albedo.x),
					fresnel(costheta, rec.albedo.y),
					fresnel(costheta, rec.albedo.z));
	double	d = ggx(wi, wo, normal, rec.attr);
	double	g = smithggx(wo, normal, rec.attr);
//	g = clamp(g, 0.000001, 0.999999);
	double	r = (d * g) / (4.0 * vec3_dot(normal, wi) * vec3_dot(normal, wo));
	r = clamp(r, 0, 1.0);
	return (vec3_mul(f, r * costheta));
}

void		microfacet(t_hit_record *rec, double *pdf, t_ray r_in)
{
	t_onb	uvw;
	t_vec3	wi;
	t_vec3	wo = vec3_unit_vector(vec3_mul(r_in.dir, -1));
	t_vec3	normal = rec->normal;

	//sample
	uvw = onb_build_from_w(rec->normal);
	t_vec3	wh = onb_local(uvw, random_microfacet_direction(rec->attr));
	wi = reflect(vec3_unit_vector(vec3_mul(wo, -1)), wh);
	rec->ray = ray(rec->p, wi);

	//pdf
	
	*pdf = microfacet_pdf(rec->attr, normal, wi, wo);
	*pdf = clamp(*pdf, 0, 1);

	//eval
//	rec->attenuation = microfacet_eval(*rec, wi, wo);
//	rec->attenuation = vec3_mul(microfacet_eval(*rec, wi, wo), *pdf);
	rec->attenuation = rec->albedo;
	return ;
}
