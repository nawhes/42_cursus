/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 05:22:17 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/21 04:07:52 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static t_vec3	random_to_sphere(double radius, double distance_squared)
{
	double	r1 = random_double();
	double	r2 = random_double();
	double	z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);

	double	phi = 2 * PI * r1;
	double	x = cos(phi) * sqrt(1 - z * z);
	double	y = sin(phi) * sqrt(1 - z * z);

	return (vec3(x, y, z));
}

static t_vec3	sphere_random(t_sphere *sp, t_vec3 o)
{
	t_vec3	direction = vec3_sub(sp->coord, o);
	double	distance_squared = vec3_length_square(direction);
	t_onb	uvw;
	uvw = onb_build_from_w(direction);
	return (onb_local(uvw, random_to_sphere(sp->diameter, distance_squared)));
}

t_vec3			light_random(t_list *p_light, t_vec3 o)
{
	int		size = ft_lstsize(p_light);
	int		target = random_int_range(0, size - 1);
	int		i = 0;
	t_list	*p_ob = p_light;
	
	while (i < target)
	{
		p_ob = p_ob->next;
		i++;
	}
	t_sphere	*sp = ((t_sphere *)((t_object *)p_ob->content)->info);
	return (sphere_random(sp, o));
}

static double	light_pdf_value(t_object *p_ob, t_ray r)
{
	t_hit_record	rec;
	rec = hit_record();
	t_sphere		*sp = (t_sphere *)p_ob->info;
	if (!p_ob->hit(*p_ob, r, &rec))
		return (0);

	double	diameter = sp->diameter;
	double	distance = vec3_length_square(vec3_sub(sp->coord, r.orig));
	double	cos_theta_max = sqrt(1 - diameter * diameter / distance);
	double	solid_angle = 2 * PI * (1 - cos_theta_max);
	return (1 / solid_angle);
}

double			light_pdf(t_list *p_light, t_ray r)
{
	double	weight = 1 / (double)ft_lstsize(p_light);
	double	sum = 0.0;
	t_list	*p_ob = p_light;
	while (p_ob)
	{
		sum += weight * light_pdf_value((t_object *)p_ob->content, r);
		p_ob = p_ob->next;
	}
	return (sum);
}
