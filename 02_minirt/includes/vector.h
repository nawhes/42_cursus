/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:46:15 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/17 07:21:52 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include "struct.h"

t_vec3				vec3(double x, double y, double z);
t_vec3				vec3_add(t_vec3 a, t_vec3 b);
t_vec3				vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				vec3_mul(t_vec3 a, double b);
t_vec3				vec3_mul_vec3(t_vec3 a, t_vec3 b);
t_vec3				vec3_div(t_vec3 a, double b);
t_vec3				vec3_div_vec3(t_vec3 a, t_vec3 b);
double				vec3_length_square(t_vec3 a);
double				vec3_length(t_vec3 a);
double				vec3_dot(t_vec3 a, t_vec3 b);
t_vec3				vec3_cross(t_vec3 a, t_vec3 b);
t_vec3				vec3_unit_vector(t_vec3 v);

t_vec3				vec3_random();
t_vec3				vec3_random_range(double min, double max);
t_vec3				vec3_random_in_unit_sphere();
t_vec3				vec3_random_unit_vector();
t_vec3				vec3_random_in_hemisphere(t_vec3 normal);

int					vec3_near_zero(t_vec3 vec);
t_vec3				reflect(t_vec3 v, t_vec3 n);
t_vec3				refract(t_vec3 uv, t_vec3 n, double etai_over_etat);

#endif
