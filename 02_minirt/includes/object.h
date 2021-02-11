/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:54:08 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/12 03:44:53 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <struct.h>

t_object	*object(void *info, int type, int texture);

t_sphere	*sphere(t_sphere this);
int			sphere_hit(t_object ob, t_ray *r, t_hit_record *rec);

t_xyrect	*xyrect(t_xyrect this);
t_xzrect	*xzrect(t_xzrect this);
t_yzrect	*yzrect(t_yzrect this);
int			xyrect_hit(t_object ob, t_ray *r, t_hit_record *rec);
int			xzrect_hit(t_object ob, t_ray *r, t_hit_record *rec);
int			yzrect_hit(t_object ob, t_ray *r, t_hit_record *rec);

void		set_record(t_object ob, t_hit_record *rec, t_vec3 albedo);
int			lambertian_scatter
	(t_ray *r_in, t_hit_record *rec, t_ray *scattered, double *pdf);
int			metal_scatter
	(t_ray *r_in, t_hit_record *rec, t_ray *scattered, double *pdf);
int			dielectric_scatter
	(t_ray *r_in, t_hit_record *rec, t_ray *scattered, double *pdf);

#endif
