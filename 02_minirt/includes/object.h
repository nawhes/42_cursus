/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:54:08 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/22 06:10:17 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <struct.h>

t_object	*object(void *info, int type, int texture);

t_sphere	*sphere(t_vec3 coord, double diameter, t_vec3 rgb);
int			sphere_hit(t_object ob, t_ray *r, t_hit_record *rec);

t_rect		*rect(double x0, double x1, double y0, double y1, double k, t_vec3 rgb);
int			rect_hit(t_object ob, t_ray *r, t_hit_record *rec);


int			lambertian_scatter
	(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);
int			metal_scatter
	(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);
int			dielectric_scatter
	(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);

#endif
