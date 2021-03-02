/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:46:15 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 09:17:11 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include "struct.h"

t_vec3				vec(double x, double y, double z);
t_vec3				vec3(double x);
t_vec3				v_inv(t_vec3 a);
t_vec3				v_add(t_vec3 a, double b);
t_vec3				v_add_v(t_vec3 a, t_vec3 b);
t_vec3				v_sub(t_vec3 a, double b);
t_vec3				v_sub_v(t_vec3 a, t_vec3 b);
t_vec3				v_mul(t_vec3 a, double b);
t_vec3				v_mul_v(t_vec3 a, t_vec3 b);
t_vec3				v_div(t_vec3 a, double b);
t_vec3				v_div_v(t_vec3 a, t_vec3 b);
double				v_length_sq(t_vec3 a);
double				v_length(t_vec3 a);
double				v_dot(t_vec3 a, t_vec3 b);
t_vec3				v_cross(t_vec3 a, t_vec3 b);
t_vec3				v_normalize(t_vec3 v);
t_vec3				v_random();
t_vec3				v_random_range(double min, double max);
t_vec3				v_random_in_unit_sphere();
t_vec3				v_random_unit_vector();
t_vec3				v_random_in_hemisphere(t_vec3 normal);
int					v_near_zero(t_vec3 vec);

#endif
