/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:54:08 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/31 05:52:58 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <struct.h>

t_object	*object(void *info, int type, int texture);

t_sphere	*sphere(t_sphere sp);
int			sphere_hit(t_object ob, t_ray *r, t_hit_record *rec);

t_rect		*rect(t_rect rectangle);
int			rect_hit(t_object ob, t_ray *r, t_hit_record *rec);


int			lambertian_scatter
	(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);
int			metal_scatter
	(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);
int			dielectric_scatter
	(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered);

#endif
