/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:00:13 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/17 20:46:05 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "struct.h"

t_viewport		*viewport_init(t_vec3 lookfrom, t_vec3 lookat, double vfov, double aspect_ratio);

void			hit_record_init(t_hit_record *this);

t_ray			ray_construct(t_vec3 orig, t_vec3 dir);
t_vec3			ray_at(t_ray a, double t);
t_vec3			ray_color(t_ray r, t_list *lst, int depth);

#endif
