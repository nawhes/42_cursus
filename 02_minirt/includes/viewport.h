/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:00:13 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/03 16:05:28 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "struct.h"

t_viewport		*viewport(t_viewport this);

t_hit_record	hit_record();

t_ray			ray(t_vec3 orig, t_vec3 dir);
t_vec3			ray_at(t_ray a, double t);
t_vec3			ray_color(t_ray r, t_minirt *rt, int depth);

#endif
